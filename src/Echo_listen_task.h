#ifndef __ECHO_LISTEN_TASK_H__
#define __ECHO_LISTEN_TASK_H__

#include "../linux_net_framework/common/Task.h"

class Echo_listen_task: public Task
{
public:
    int initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj);

private:
    void echo_listen_cb(Listener *plistener, int fd, HVN::Sock_addr_v4 sa);
    Listener *m_plistener;
};

#endif

