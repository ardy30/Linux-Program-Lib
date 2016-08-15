#include <cassert>
#include <tr1/functional>
#include "linux_program_libs/log/log.h"
#include "linux_net_framework/common/Task_factory.h"
#include "Echo_listen_task.h"
#include "Echo_task.h"

int Echo_listen_task::initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj)
{
    this->m_plistener = this->open_listener();
    HVN::Sock_addr_v4 sa;
    sa.set_ip("0.0.0.0");
    sa.set_port(63211);
    if(this->m_plistener->initial_and_listen(this, sa, 1000, std::tr1::bind(&Echo_listen_task::echo_listen_cb, this, 
                    std::tr1::placeholders::_1, std::tr1::placeholders::_2, std::tr1::placeholders::_3)))
    {
        LOGGING_ERROR("Echo_listen_task::initial - initial_and_listen");
        return -1;
    }
    return 0;
}

void Echo_listen_task::echo_listen_cb(Listener *plistener, int fd, HVN::Sock_addr_v4 sa)
{
    Echo_task *ptask = Task_factory::get_pinstance()->new_task<Echo_task>();
    ptask->initial((void *)fd, NULL);
}

