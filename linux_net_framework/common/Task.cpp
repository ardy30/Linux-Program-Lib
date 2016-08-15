#include "Task.h"
#include "Resource_factory.h"

int Task::recycle(void)
{
    if(this->m_is_recycled)
        return 0;
    this->m_is_recycled = 1;

    std::set<Sock *>::iterator p_sock_iterator;
    for (
            p_sock_iterator = this->m_sock_set.begin();
            p_sock_iterator != this->m_sock_set.end();
            p_sock_iterator++
        )
        Resource_factory<Sock>::get_pinstance()->recycle(*p_sock_iterator);
    this->m_sock_set.clear();

    std::set<Sock_nh *>::iterator p_sock_nh_iterator;
    for (
            p_sock_nh_iterator = this->m_sock_nh_set.begin();
            p_sock_nh_iterator != this->m_sock_nh_set.end();
            p_sock_nh_iterator++
        )
        Resource_factory<Sock_nh>::get_pinstance()->recycle(*p_sock_nh_iterator);
    this->m_sock_nh_set.clear();

    std::set<Listener *>::iterator p_listener_iterator;
    for (
            p_listener_iterator = this->m_listener_set.begin();
            p_listener_iterator != this->m_listener_set.end();
            p_listener_iterator++
        )
        Resource_factory<Listener>::get_pinstance()->recycle(*p_listener_iterator);
    this->m_listener_set.clear();

    std::set<Timer *>::iterator p_timer_iterator;
    for (
            p_timer_iterator = this->m_timer_set.begin();
            p_timer_iterator != this->m_timer_set.end();
            p_timer_iterator++
        )
        Resource_factory<Timer>::get_pinstance()->recycle(*p_timer_iterator);
    this->m_timer_set.clear();
    
    return 0;
}

int Task::is_recycled(void) const
{
    return this->m_is_recycled;
}

int Task::get_task_type(void) const
{
    return this->m_task_type;
}

std::string Task::get_task_discribe(void) const
{
    return this->m_task_discribe;
}

int Task::get_nr_req(void) const
{
    return this->m_nr_req;
}

void Task::inc_nr_req(void)
{
    this->m_nr_req++;
}

void Task::dec_nr_req(void)
{
    this->m_nr_req--;
}

Sock *Task::open_sock(void)
{
    Sock *ptr = Resource_factory<Sock>::get_pinstance()->new_resource();
    this->m_sock_set.erase(ptr);
    this->m_sock_set.insert(ptr);
    return ptr;
}

void Task::close_sock(Sock *ptr)
{
    this->m_sock_set.erase(ptr);
    Resource_factory<Sock>::get_pinstance()->recycle(ptr);
}

Sock_nh *Task::open_sock_nh(void)
{
    Sock_nh *ptr = Resource_factory<Sock_nh>::get_pinstance()->new_resource();
    this->m_sock_nh_set.erase(ptr);
    this->m_sock_nh_set.insert(ptr);
    return ptr;
}

void Task::close_sock_nh(Sock_nh *ptr)
{
    this->m_sock_nh_set.erase(ptr);
    Resource_factory<Sock_nh>::get_pinstance()->recycle(ptr);
}

Listener *Task::open_listener(void)
{
    Listener *ptr = Resource_factory<Listener>::get_pinstance()->new_resource();
    this->m_listener_set.erase(ptr);
    this->m_listener_set.insert(ptr);
    return ptr;
}

void Task::close_listener(Listener *ptr)
{
    this->m_listener_set.erase(ptr);
    Resource_factory<Listener>::get_pinstance()->recycle(ptr);
}

Timer *Task::open_timer(void)
{
    Timer *ptr = Resource_factory<Timer>::get_pinstance()->new_resource();
    this->m_timer_set.erase(ptr);
    this->m_timer_set.insert(ptr);
    return ptr;
}

void Task::close_timer(Timer *ptr)
{
    this->m_timer_set.erase(ptr);
    Resource_factory<Timer>::get_pinstance()->recycle(ptr);
}

