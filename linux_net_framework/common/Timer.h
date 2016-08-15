#ifndef __TIMER_H__
#define __TIMER_H__

#include <event2/event.h>
#include <event2/util.h>
#include <tr1/functional>
#include "../../linux_program_libs/utils/Time.h"
#include "../../linux_program_libs/utils/Noncopyable.h"

class Task;

class Timer: public HVN::Noncopyable
{
public:
    Timer(void): m_timer(NULL), m_is_persist(0), m_is_recycled(0), m_cb_obj(NULL), m_ptask(NULL) {}
    ~Timer(void) { this->recycle(); }

public:
    void recycle(void);
    int is_recycled(void) const;

public:
    int initial(Task *ptask, int is_persist, std::tr1::function<void (Timer *)> cb_obj);
    int begin(HVN::Time &tm) const;
    int end(void) const;
    int pending(HVN::Time &tm) const;
    int is_persist(void) const;

private:
    static void timer_cb(evutil_socket_t fd, short what, void *arg);

private:
    event *m_timer;
    int m_is_persist;
    int m_is_recycled;
    std::tr1::function<void (Timer *)> m_cb_obj;
    Task *m_ptask;
};

#endif

