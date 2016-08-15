#include <cstdlib>
#include <tr1/functional>
#include "../../linux_program_libs/log/log.h"
#include "Basic_config_manager.h"
#include "Work_item.h"
#include "Middle_server_task.h"

Middle_server_task *g_pmiddle_server_task = NULL;

int Middle_server_task::initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj)
{
    this->m_plistener = this->open_listener();
    HVN::Sock_addr_v4 sa;
    sa.set_ip("0.0.0.0");
    sa.set_port(Basic_config_manager::get_pinstance()->get_middle_server_port());
    if(this->m_plistener->initial_and_listen(this, sa, 1, std::tr1::bind(&Middle_server_task::cmd_listen_cb, 
                    this, std::tr1::placeholders::_1, std::tr1::placeholders::_2, std::tr1::placeholders::_3)))
    {
        LOGGING_FATAL("initial_and_listen");
        std::exit(-1);
    }
    return 0;
}

int Middle_server_task::put_work(Task *ptask, std::tr1::function<int (void *)> work_fn_obj, void *arg, std::tr1::function<void (int, void *)> reply_fn_obj)
{
    if(!this->m_psock_nh)
    {
        LOGGING_ERROR("middle server uninit sock_nh");
        return -1;
    }

    this->m_psock_nh->write_enable();
    Work_item *pwork_item = new Work_item(ptask, work_fn_obj, arg, reply_fn_obj);
    if(this->m_psock_nh->send_data((void *)&pwork_item, sizeof(pwork_item)))
    {
        LOGGING_ERROR("send_data");
        delete pwork_item;
        return -1;
    }
    return 0;
}

void Middle_server_task::cmd_listen_cb(Listener *plistener, int fd, HVN::Sock_addr_v4 sa)
{
    this->close_listener(this->m_plistener);
    this->m_plistener = NULL;

    this->m_psock_nh = this->open_sock_nh();
    if(this->m_psock_nh->initial(this, fd, NULL, NULL, std::tr1::bind(&Middle_server_task::cmd_sock_nh_cb, this, 
                    std::tr1::placeholders::_1, std::tr1::placeholders::_2, std::tr1::placeholders::_3, std::tr1::placeholders::_4)))
    {
        LOGGING_FATAL("middle server sock init");
        std::exit(-1);
    }
    this->m_psock_nh->read_enable();
    this->m_psock_nh->write_disable();
}

void Middle_server_task::cmd_sock_nh_cb(Sock_nh *psock_nh, int type, char *buf, int len)
{
    switch(type)
    {
    case NH_READ_CB:
        do{
            Work_item **work_item_buf = (Work_item **)buf;
            int req_num = len / sizeof(Work_item *);
            for(int i = 0; i < req_num; i++)
            {
                Work_item *pwork_item = work_item_buf[i];
                pwork_item->reply();
                delete pwork_item;
            }
        }while(0);
        break;

    case NH_WRITE_CB:
        this->m_psock_nh->write_disable();
        break;

    case NH_CONNECT_CB:
        LOGGING_FATAL("Middle server connection error");
        break;

    case NH_EOF_CB:
        LOGGING_FATAL("Middle server connection closed");
        break;

    case NH_ERROR_CB:
        LOGGING_FATAL("Middle server connection error");
        break;

    case NH_READ_TIMEOUT_CB:
        LOGGING_FATAL("Middle server connection error");
        break;

    case NH_WRITE_TIMEOUT_CB:
        LOGGING_FATAL("Middle server connection error");
        break;

    default:
        LOGGING_FATAL("Middle server connection error");
        break;
    }
}

