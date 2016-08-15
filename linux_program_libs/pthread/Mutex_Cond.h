/*
 * =====================================================================================
 *
 *       Filename:  Mutex_Cond.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 16:48:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_MUTEX_COND_H__
#define __HVN_MUTEX_COND_H__

#include <pthread.h>
#include <errno.h>
#include <cstring>
#include "../utils/Noncopyable.h"
#include "../utils/Time.h"
#include "../log/log.h"

namespace HVN
{

class Mutex: public Noncopyable
{
private:
    friend class Cond;

public:
    Mutex(int is_recursive = 0)
    {
        pthread_mutexattr_t attr;
        pthread_mutexattr_t *pattr = NULL;
        if(pthread_mutexattr_init(&attr))
        {
            LOGGING_WARN(std::strerror(errno));
            pattr = NULL;
        }
        else
        {
            if(is_recursive)
            {
                if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE))
                    LOGGING_WARN(std::strerror(errno));
            }
            pattr = &attr;
        }
        if(pthread_mutex_init(&this->m_mutex, pattr))
            LOGGING_ERROR(std::strerror(errno));
        if(pthread_mutexattr_destroy(&attr))
            LOGGING_WARN(std::strerror(errno));
    }
    ~Mutex(void)
    { if(pthread_mutex_destroy(&this->m_mutex)) LOGGING_WARN(std::strerror(errno)); }
 
public:
    void lock(void)
    { if(pthread_mutex_lock(&this->m_mutex)) LOGGING_ERROR(std::strerror(errno)); }
    void unlock(void)
    { if(pthread_mutex_unlock(&this->m_mutex)) LOGGING_ERROR(std::strerror(errno)); }
    int trylock(void)
    { return pthread_mutex_trylock(&this->m_mutex); }

private:
    pthread_mutex_t m_mutex;
};
  
class Mutex_lock: public Noncopyable
{
public:
    explicit Mutex_lock(Mutex &rmutex): m_rmutex(rmutex)
    { this->m_rmutex.lock(); }
    ~Mutex_lock(void)
    { this->m_rmutex.unlock(); }

private:
    Mutex &m_rmutex;
};

class Cond: public Noncopyable
{
public:
    explicit Cond(Mutex &rmutex): m_rmutex(rmutex)
    { if(pthread_cond_init(&this->m_cond, NULL)) LOGGING_ERROR(std::strerror(errno)); }
    ~Cond(void)
    { if(pthread_cond_destroy(&this->m_cond)) LOGGING_WARN(std::strerror(errno)); }

public:
    void wait(void)
    { if(pthread_cond_wait(&this->m_cond, &this->m_rmutex.m_mutex)) LOGGING_ERROR(std::strerror(errno)); }
    int abs_timed_wait(Time &tm) 
    {
        struct timespec timeout = tm.to_timespec();
        return pthread_cond_timedwait(&this->m_cond, &this->m_rmutex.m_mutex, &timeout);
    }
    int rel_timed_wait(Time &tm)
    {
        Time abs_tm;
        abs_tm.now();
        abs_tm += tm;
        return this->abs_timed_wait(abs_tm);
    }
    void notify(void)
    { if(pthread_cond_signal(&this->m_cond)) LOGGING_ERROR(std::strerror(errno)); }
    void notify_all(void)
    { if(pthread_cond_broadcast(&this->m_cond)) LOGGING_ERROR(std::strerror(errno)); }

private:
    Mutex &m_rmutex;
    pthread_cond_t m_cond;
};

class Event
{
public:
    Event(void): m_mutex(), m_cond(m_mutex), m_wait(0), m_wait_count(0) {}

public:
    void wait(void)
    {   
        Mutex_lock lock(this->m_mutex);
        this->m_wait_count++;
        while(!this->m_wait)
            this->m_cond.wait();
        if(!--this->m_wait_count)
        this->m_wait = 0;
    }   

    void notify(void)
    {   
        Mutex_lock lock(this->m_mutex);
        this->m_wait = 1;
        this->m_cond.notify_all();
    }   

private:
    Mutex m_mutex;
    Cond m_cond;
    int m_wait;
    int m_wait_count;
};

} //namespace HVN

#endif

