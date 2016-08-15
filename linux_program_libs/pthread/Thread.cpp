/*
 * =====================================================================================
 *
 *       Filename:  Thread.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/01/11 23:15:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include "Thread.h"

void *HVN::Thread::thread_function(void *arg)
{
    Thread *pthis = (Thread *)arg;
    if(!pthis->m_can_cancel)
    {
        int old_state;
        if(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state))
            LOGGING_WARN(std::strerror(errno));
    }
    if(pthis->m_can_cancel && pthis->m_immediate_cancel)
    {
        int old_type;
        if(pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_type))
            LOGGING_WARN(std::strerror(errno));
    }
    pthis->work_function();
    return NULL;
}

int HVN::Thread::start(int is_detach, int stack_size, int can_cancel, int immediate_cancel)
{
    if(this->is_active())
    {
        LOGGING_ERROR("already running");
        return -1;
    }
    if(is_detach)
    {
        if(pthread_attr_setdetachstate(&this->m_attr, PTHREAD_CREATE_DETACHED))
            LOGGING_WARN(std::strerror(errno));
    }
    if(stack_size)
    {
        if(pthread_attr_setstacksize(&this->m_attr, stack_size))
            LOGGING_WARN(std::strerror(errno));
    }
    this->m_can_cancel = can_cancel;
    this->m_immediate_cancel = immediate_cancel;
    if(pthread_create(&this->m_tid, &this->m_attr, &Thread::thread_function, this))
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}




