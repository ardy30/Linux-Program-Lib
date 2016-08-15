/*
 * =====================================================================================
 *
 *       Filename:  Thread.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/29/11 18:30:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_THREAD_H__
#define __HVN_THREAD_H__

#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <cstring>
#include "../utils/Noncopyable.h"
#include "../log/log.h" 

namespace HVN
{

class Thread: public Noncopyable
{
public:
    Thread(void): m_tid(0) 
    { if(pthread_attr_init(&this->m_attr)) LOGGING_ERROR(std::strerror(errno)); }
    ~Thread(void) 
    { if(is_active()) LOGGING_WARN("thread still running, control data lost"); pthread_attr_destroy(&this->m_attr); }

protected:
    virtual void work_function(void) = 0;

public:
    int start(int is_detach = 0, int stack_size = 0, int can_cancel = 1, int immediate_cancel = 0);
    void join(void) { if(pthread_join(this->m_tid, NULL)) LOGGING_WARN(std::strerror(errno)); }
    void cancel(void) { if(pthread_cancel(this->m_tid)) LOGGING_WARN(std::strerror(errno)); }
    int is_active(void) const { return pthread_kill(this->m_tid, 0) == 0 ? 1 : 0; }
    pthread_t get_tid(void) const { return this->m_tid; }

private:
    static void *thread_function(void *arg);

private:
    pthread_t           m_tid;
    pthread_attr_t      m_attr;
    int                 m_can_cancel;
    int                 m_immediate_cancel;
};

} // namespace HVN

#endif

