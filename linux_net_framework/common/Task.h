#ifndef __TASK_H__
#define __TASK_H__

#include <set>
#include <tr1/functional>
#include <event2/util.h>
#include "../../linux_program_libs/utils/Noncopyable.h"
#include "Sock.h"
#include "Sock_nh.h"
#include "Listener.h"
#include "Timer.h"

class Task: public HVN::Noncopyable
{
public:
    Task(void): m_task_type(-1), m_task_discribe("default discribe"), m_is_recycled(0), m_task_state(-1), m_nr_req(0), m_result_cb_obj(NULL) {}
    virtual ~Task(void) { this->recycle(); }

public:
    int recycle(void);
    int is_recycled(void) const;

public:
    virtual int initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj) = 0;

public:
    int get_task_type(void) const;
    std::string get_task_discribe(void) const;

    int get_nr_req(void) const;
    void inc_nr_req(void);
    void dec_nr_req(void);

protected:
    Sock *open_sock(void);
    void close_sock(Sock *ptr);

    Sock_nh *open_sock_nh(void);
    void close_sock_nh(Sock_nh *ptr);

    Listener *open_listener(void);
    void close_listener(Listener *ptr);

    Timer *open_timer(void);
    void close_timer(Timer *ptr);

protected:
    int m_task_type;
    std::string m_task_discribe;
    int m_is_recycled;
    int m_task_state;
    int m_nr_req;

    std::tr1::function<void (Task *, int, void *)> m_result_cb_obj;
    std::set<Sock *> m_sock_set;
    std::set<Sock_nh *> m_sock_nh_set;
    std::set<Listener *> m_listener_set;
    std::set<Timer *> m_timer_set;
};

#endif

