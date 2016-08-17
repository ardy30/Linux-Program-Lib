#include <iostream>
#include <string>
#include <tr1/functional>
#include "../linux_program_libs/log/log.h"
#include "../linux_net_framework/common/Task_factory.h"
#include "../linux_net_framework/component/Middle_server_task.h"
#include "Echo_task.h"

int Echo_task::initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj)
{
    intptr_t fd = (long)arg;
    this->m_psock_nh = this->open_sock_nh();
    if(this->m_psock_nh->initial(this, fd, NULL, NULL, std::tr1::bind(&Echo_task::echo_sock_nh_cb, this, std::tr1::placeholders::_1, 
                    std::tr1::placeholders::_2, std::tr1::placeholders::_3, std::tr1::placeholders::_4)))
    {
        LOGGING_ERROR("Echo_task::initial - initial");
        return -1;
    }
    this->m_psock_nh->read_enable();
    return 0;
}

void Echo_task::echo_sock_nh_cb(Sock_nh *psock_nh, int type, char *buf, int len)
{
    switch(type)
    {
    case NH_READ_CB:
        this->do_echo(buf, len);
        break;

    case NH_WRITE_CB:
        break;

    case NH_EOF_CB:
        LOGGING_INFO("closed by peer");
        this->close_sock_nh(this->m_psock_nh);
        this->m_psock_nh = NULL;
        Task_factory::get_pinstance()->recycle(this);
        break;

    case NH_ERROR_CB:
        LOGGING_INFO("an error");
        this->close_sock_nh(this->m_psock_nh);
        this->m_psock_nh = NULL;
        Task_factory::get_pinstance()->recycle(this);
        break;

    case NH_READ_TIMEOUT_CB:
        break;

    case NH_WRITE_TIMEOUT_CB:
        break;

    default:
        break;

    }
}

void Echo_task::do_echo(char *buf, int len)
{
    this->m_echo_str.assign(buf, len);
    g_pmiddle_server_task->put_work(this, std::tr1::bind(&Echo_task::work_fn, this, "hahaha", std::tr1::placeholders::_1), 
            (void *)"hahaeeee", std::tr1::bind(&Echo_task::reply_fn, this, std::tr1::placeholders::_1, std::tr1::placeholders::_2));
}

int Echo_task::work_fn(std::string str, void *arg)
{
    for(volatile int i = 0; i < 5000; i++);
    return 0;
}

void Echo_task::reply_fn(int success, void *arg)
{
    this->m_psock_nh->send_data(this->m_echo_str.c_str(), this->m_echo_str.length());
}


