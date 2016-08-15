#include <cassert>
#include "Timer.h"
#include "Scheduler.h"
#include "../../linux_program_libs/log/log.h"

void Timer::recycle(void)
{
    if(this->m_is_recycled)
        return;
    this->m_is_recycled = 1;
    if(this->m_timer)
    {
        event_free(this->m_timer);
        this->m_timer = NULL;
    }
    this->m_ptask = NULL;
}

int Timer::is_recycled(void) const
{
    return this->m_is_recycled;
}

void Timer::timer_cb(evutil_socket_t fd, short what, void *arg)
{
    Timer *pthis = (Timer *)arg;
    pthis->m_cb_obj(pthis);
}

int Timer::initial(Task *ptask, int is_persist, std::tr1::function<void (Timer *)> cb_obj)
{
    assert(cb_obj != NULL);
    this->m_ptask = ptask;
    this->m_cb_obj = cb_obj;
    if(is_persist)
        this->m_is_persist = EV_PERSIST;
    else
        this->m_is_persist = 0;
    this->m_timer = event_new(Scheduler::get_pinstance()->get_base(), -1, this->m_is_persist, &Timer::timer_cb, this);
    if(!this->m_timer)
    {
        LOGGING_ERROR("event_new");
        return -1;
    }
    return 0;
}

int Timer::begin(HVN::Time &tm) const
{
    timeval temp_tv = tm.to_timeval();
    return event_add(this->m_timer, &temp_tv);
}

int Timer::end(void) const
{
    return event_del(this->m_timer);
}

int Timer::pending(HVN::Time &tm) const
{
    timeval temp_tv;
    int ret = event_pending(this->m_timer, EV_TIMEOUT, &temp_tv);
    tm.set(temp_tv);
    return ret;
}

int Timer::is_persist(void) const
{
    return this->m_is_persist;
}

