#ifndef __RESOURCE_FACTORY_H__
#define __RESOURCE_FACTORY_H__

#include <set>
#include "../../linux_program_libs/utils/Singleton.h"

template<typename T>
class Resource_factory: public HVN::Singleton<Resource_factory<T> >
{
private:
    friend class HVN::Singleton<Resource_factory>;
    Resource_factory(void) {}

private:
    friend class Task;
    friend class Task_factory;
    T *new_resource(void);
    void recycle(T *ptr);
    void clear_recycle(void);

private:
    std::set<T *> m_available_resource_set;
    std::set<T *> m_recycle_resource_set;
};

template<typename T>
void Resource_factory<T>::recycle(T *ptr)
{
    if(ptr == NULL)
        return;  
    this->m_available_resource_set.erase(ptr);
    ptr->recycle();
    this->m_recycle_resource_set.erase(ptr);
    this->m_recycle_resource_set.insert(ptr);
}

template<typename T>
void Resource_factory<T>::clear_recycle(void)
{
    typename std::set<T *>::iterator p_resource_iterator;
    for (
            p_resource_iterator = this->m_recycle_resource_set.begin();
            p_resource_iterator != this->m_recycle_resource_set.end();
            p_resource_iterator++
        )
        delete *p_resource_iterator;

    this->m_recycle_resource_set.clear();
}

template<typename T>
T *Resource_factory<T>::new_resource(void)
{
    T *ptr = NULL;
    ptr = new T();
    this->m_available_resource_set.erase(ptr);
    this->m_available_resource_set.insert(ptr);
    return ptr;
}

#endif

