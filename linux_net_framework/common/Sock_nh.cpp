#include <cassert>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/event.h>
#include "../../linux_program_libs/net/Tcp_v4_socket.h"
#include "../../linux_program_libs/log/log.h"
#include "Sock_nh.h"
#include "Scheduler.h"

void Sock_nh::recycle(void)
{
    if(this->m_is_recycled)
        return;
    this->m_is_recycled = 1;
    if(this->m_bev)
    {
        bufferevent_free(this->m_bev);
        this->m_bev = NULL;
    }
    this->m_ptask = NULL;
}

int Sock_nh::is_recycled(void) const
{
    return this->m_is_recycled;
}

void Sock_nh::read_cb(bufferevent *bev, void *arg)
{
    Sock_nh *pthis = (Sock_nh *)arg;
    evbuffer *input = bufferevent_get_input(bev);
    while(evbuffer_get_length(input))
    {
        char buf[4096];
        size_t len = bufferevent_read(bev, buf, sizeof(buf));
        pthis->m_cb_obj(pthis, NH_READ_CB, buf, len);
    }
}

void Sock_nh::write_cb(bufferevent *bev, void *arg)
{
    Sock_nh *pthis = (Sock_nh *)arg;
    evbuffer *output = bufferevent_get_output(bev);
    if(evbuffer_get_length(output) == 0) 
        pthis->m_cb_obj(pthis, NH_WRITE_CB, NULL, 0);
}

void Sock_nh::event_cb(bufferevent *bev, short what, void *arg)
{
    Sock_nh *pthis = (Sock_nh *)arg;
    if(what & BEV_EVENT_EOF)
        pthis->m_cb_obj(pthis, NH_EOF_CB, NULL, 0);
    else if(what & BEV_EVENT_ERROR)
        pthis->m_cb_obj(pthis, NH_ERROR_CB, NULL, 0);
    else if((what & (BEV_EVENT_TIMEOUT | BEV_EVENT_READING)) == (BEV_EVENT_TIMEOUT | BEV_EVENT_READING))
        pthis->m_cb_obj(pthis, NH_READ_TIMEOUT_CB, NULL, 0);
    else if((what & (BEV_EVENT_TIMEOUT | BEV_EVENT_WRITING)) == (BEV_EVENT_TIMEOUT | BEV_EVENT_WRITING))
        pthis->m_cb_obj(pthis, NH_WRITE_TIMEOUT_CB, NULL, 0);
    else if(what & BEV_EVENT_CONNECTED)
        pthis->m_cb_obj(pthis, NH_CONNECT_CB, NULL, 0);
}

int Sock_nh::initial(Task *ptask, evutil_socket_t fd, HVN::Time *pcrtv, HVN::Time *pcwtv, std::tr1::function<void (Sock_nh *, int, char *, int)> cb_obj)
{
    timeval temp_rtv, temp_wtv;
    timeval *ptemp_rtv = NULL;
    timeval *ptemp_wtv = NULL;

    assert(cb_obj != NULL);
    this->m_ptask = ptask;
    this->m_cb_obj = cb_obj;
    this->m_bev = bufferevent_socket_new(Scheduler::get_pinstance()->get_base(), fd, BEV_OPT_CLOSE_ON_FREE);
    if (!this->m_bev) 
    {
        LOGGING_ERROR("bufferevent_socket_new");
        return -1;
    }
    bufferevent_setcb(this->m_bev, &Sock_nh::read_cb, &Sock_nh::write_cb, &Sock_nh::event_cb, this);

    if(pcrtv)
    {
        temp_rtv = pcrtv->to_timeval();
        ptemp_rtv = &temp_rtv;
    }
    if(pcwtv)
    {
        temp_wtv = pcwtv->to_timeval();
        ptemp_wtv = &temp_wtv;
    }
    bufferevent_set_timeouts(this->m_bev, ptemp_rtv, ptemp_wtv);
    return 0;
}

int Sock_nh::connect(HVN::Sock_addr_v4 &csa) const
{
    sockaddr_in sin = csa.get_sockaddr_in();
    return bufferevent_socket_connect(this->m_bev, (sockaddr*)&sin, sizeof(sockaddr_in));
}

int Sock_nh::send_data(const void *data, size_t size) const
{
    return bufferevent_write(this->m_bev, data, size);
}

HVN::Sock_addr_v4 Sock_nh::get_peer_addr(void) const
{
    int fd = bufferevent_getfd(this->m_bev);
    HVN::Tcp_v4_socket tcp_socket(fd);
    HVN::Sock_addr_v4 sa;
    if(tcp_socket.get_peer_addr(sa))
        LOGGING_ERROR("get_peer_addr");
    return sa;
}

HVN::Sock_addr_v4 Sock_nh::get_local_addr(void) const
{
    int fd = bufferevent_getfd(this->m_bev);
    HVN::Tcp_v4_socket tcp_socket(fd);
    HVN::Sock_addr_v4 sa;
    if(tcp_socket.get_local_addr(sa))
        LOGGING_ERROR("get_local_addr");
    return sa;
}


bool Sock_nh::is_read_enable(void) const
{
    short what = bufferevent_get_enabled(this->m_bev);
    if(what & EV_READ)
        return true;
    else
        return false;
}

bool Sock_nh::is_write_enable(void) const
{
    short what = bufferevent_get_enabled(this->m_bev);
    if(what & EV_WRITE)
        return true;
    else
        return false;
}

int Sock_nh::read_enable(void) const
{
    return bufferevent_enable(this->m_bev, EV_READ);
}

int Sock_nh::read_disable(void) const
{
    return bufferevent_disable(this->m_bev, EV_READ);
}

int Sock_nh::write_enable(void) const
{
    return bufferevent_enable(this->m_bev, EV_WRITE);
}

int Sock_nh::write_disable(void) const
{
    return bufferevent_disable(this->m_bev, EV_WRITE);
}

