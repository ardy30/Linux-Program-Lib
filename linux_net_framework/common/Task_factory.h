#ifndef __TASK_FACTORY_H__
#define __TASK_FACTORY_H__

#include <string>
#include <set>
#include <list>
#include "../../linux_program_libs/utils/Singleton.h"

class Task;

class Task_factory: public HVN::Singleton<Task_factory>
{
    struct Task_item 
    {
        long task_index;
        int task_type;
        std::string task_discribe;
    };

private:
    friend class HVN::Singleton<Task_factory>;
    Task_factory(void) {}

public:
    template<typename T> T *new_task(void)
    {
        Task *ptr = new T();
        this->m_available_task_set.erase(ptr);
        this->m_available_task_set.insert(ptr);
        return (T *)ptr;
    }
    void recycle(Task *ptr);
    void clear_recycle(void);
    void task_list(std::list<Task_item> &lst);
    int task_kill(long task_index);

private:
    std::set<Task *>    m_available_task_set;
    std::set<Task *>    m_recycle_task_set;
};

#endif

