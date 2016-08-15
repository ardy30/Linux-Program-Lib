#include <cassert>
#include "Listener.h"
#include "Scheduler.h"
#include "../../linux_program_libs/log/log.h"

void Listener::recycle(void)
{
    if(this->m_is_recycled)
        return;
    this->m_is_recycled = 1;
    if(this->m_listener)
    {
        evconnlistener_free(this->m_listener);
        this->m_listener = NULL;
    }
    this->m_ptask = NULL;
}

int Listener::is_recycled(void) const
{
    return this->m_is_recycled;
}

void Listener::listen_cb(evconnlistener *listener, evutil_socket_t fd, sockaddr *sa, int socklen, void *arg)
{
    Listener *pthis = (Listener *)arg;
    sockaddr_in *psa = (sockaddr_in *)sa;
    HVN::Sock_addr_v4 temp_sa;
    temp_sa.set_by_sockaddr_in(*psa);
    pthis->m_cb_obj(pthis, fd, temp_sa);
}

int Listener::initial_and_listen(Task *ptask, HVN::Sock_addr_v4 &sa, int backlog, std::tr1::function<void (Listener *, int, HVN::Sock_addr_v4)> cb_obj)
{
    assert(cb_obj != NULL);
    this->m_ptask = ptask;
    this->m_cb_obj = cb_obj;
    sockaddr_in sin;
    sin = sa.get_sockaddr_in();
    this->m_listener = evconnlistener_new_bind(Scheduler::get_pinstance()->get_base(), &Listener::listen_cb, this, 
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, backlog, (sockaddr*)&sin, sizeof(sockaddr_in));
    if(!this->m_listener)
    {
        LOGGING_ERROR("evconnlistener_new_bind");
        return -1;
    }
    return 0;
}

