#ifndef __ECHO_TASK_H__
#define __ECHO_TASK_H__

#include <string>
#include "../linux_net_framework/common/Task.h"

class Echo_task: public Task
{
public:
    virtual int initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj);

private:
    void do_echo(char *buf, int len);
    int work_fn(std::string str, void *arg);
    void reply_fn(int success, void *arg);   

private:
    void echo_sock_nh_cb(Sock_nh *pagent_nh, int type, char *buf, int len);
    Sock_nh *m_psock_nh;

    std::string m_echo_str;
};

#endif

