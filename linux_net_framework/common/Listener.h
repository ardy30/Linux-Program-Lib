#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <event2/listener.h>
#include <tr1/functional>
#include "../../linux_program_libs/utils/Noncopyable.h"
#include "../../linux_program_libs/net/Sock_addr_v4.h"

class Task;

class Listener: public HVN::Noncopyable
{
public:
    Listener(void): m_listener(NULL), m_is_recycled(0), m_cb_obj(NULL), m_ptask(NULL) {}
    ~Listener(void) { this->recycle(); }

public:
    void recycle(void);
    int is_recycled(void) const;

public:
    int initial_and_listen(Task *ptask, HVN::Sock_addr_v4 &sa, int backlog, std::tr1::function<void (Listener *, int, HVN::Sock_addr_v4)> cb_obj);

private:
    static void listen_cb(evconnlistener *listener, evutil_socket_t fd, sockaddr *sa, int socklen, void *arg);

private:
    evconnlistener *m_listener;
    int m_is_recycled;
    std::tr1::function<void (Listener *, int, HVN::Sock_addr_v4)> m_cb_obj;
    Task *m_ptask;
};

#endif

