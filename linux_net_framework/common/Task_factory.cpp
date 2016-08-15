#include "Task.h"
#include "Task_factory.h"
#include "Resource_factory.h"

void Task_factory::recycle(Task *ptr)
{   
    this->m_available_task_set.erase(ptr);
    ptr->recycle();
    this->m_recycle_task_set.erase(ptr);
    this->m_recycle_task_set.insert(ptr);
}

void Task_factory::clear_recycle(void)
{
    std::set<Task *> temp_task_set;
    std::set<Task *>::iterator p_task_iterator;
    for (
            p_task_iterator = this->m_recycle_task_set.begin();
            p_task_iterator != this->m_recycle_task_set.end();
            p_task_iterator++
        )
    {
        if((*p_task_iterator)->get_nr_req())
            temp_task_set.insert(*p_task_iterator);
        else
            delete *p_task_iterator;
    }
    this->m_recycle_task_set = temp_task_set;

//recycle resource
    Resource_factory<Sock>::get_pinstance()->clear_recycle();
    Resource_factory<Sock_nh>::get_pinstance()->clear_recycle();
    Resource_factory<Listener>::get_pinstance()->clear_recycle();
    Resource_factory<Timer>::get_pinstance()->clear_recycle();
}

void Task_factory::task_list(std::list<Task_item> &lst)
{
    lst.clear();
    std::set<Task *>::iterator p_task_iterator;
    for (
            p_task_iterator = this->m_available_task_set.begin();
            p_task_iterator != this->m_available_task_set.end();
            p_task_iterator++
        )
    {
        Task_item ti;
        ti.task_index = (long)(*p_task_iterator);
        ti.task_type = (*p_task_iterator)->get_task_type();
        ti.task_discribe = (*p_task_iterator)->get_task_discribe();
        lst.push_back(ti);
    }
}

int Task_factory::task_kill(long task_index)
{
    Task *ptr = (Task *)task_index;
    std::set<Task *>::iterator resault = this->m_available_task_set.find(ptr);
    if(resault == this->m_available_task_set.end())
        return -1;
    this->recycle(ptr);
    return 0;
}

