/*
 * =====================================================================================
 *
 *       Filename:  Singleton.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 19:44:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_SINGLETON_H__
#define __HVN_SINGLETON_H__

#include <pthread.h>

namespace HVN
{

template <typename T>
class Singleton
{
private:
    Singleton(const Singleton&);
    Singleton &operator=(const Singleton&);

public:
    virtual ~Singleton(void) {}
    static T *get_pinstance(void);

protected:
    Singleton(void) {}

private:
    static T *m_pinstance;
    static pthread_mutex_t m_init_mutex;
};

template <typename T>
T *Singleton<T>::m_pinstance = NULL;

template <typename T>
pthread_mutex_t Singleton<T>::m_init_mutex = PTHREAD_MUTEX_INITIALIZER;

template <typename T>
T *Singleton<T>::get_pinstance(void)
{
    if(m_pinstance == NULL)
    {
        if(pthread_mutex_lock(&m_init_mutex))
            return NULL;
        if(m_pinstance == NULL)
            m_pinstance = new T;
        if(pthread_mutex_unlock(&m_init_mutex))
            return NULL;
    }
    return m_pinstance;
}

} //namespace HVN

#endif

