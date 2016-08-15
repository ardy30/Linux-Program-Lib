#ifndef __MIDDLE_SERVER_TASK_H__
#define __MIDDLE_SERVER_TASK_H__

#include "../common/Task.h"

class Middle_server_task: public Task
{
public:
    Middle_server_task(void): m_plistener(NULL), m_psock_nh(NULL)
    { 
        this->m_task_type = 1; 
        this->m_task_discribe = "middle server task"; 
    }
    ~Middle_server_task(void) {}

public:
    virtual int initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj);
    int put_work(Task *ptask, std::tr1::function<int (void*)> work_fn_obj, void *arg, std::tr1::function<void (int, void *)> reply_fn_obj);

private:
    void cmd_listen_cb(Listener *plistener, int fd, HVN::Sock_addr_v4 sa);
    Listener *m_plistener;

    void cmd_sock_nh_cb(Sock_nh *psock_nh, int type, char *buf, int len);
    Sock_nh *m_psock_nh;
};

extern Middle_server_task *g_pmiddle_server_task;

#endif


