/*
 * =====================================================================================
 *
 *       Filename:  Signal_manager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/11 22:14:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <cstdlib>
#include "Signal_manager.h"
#include "../log/log.h"

int HVN::Signal_manager::register_signal(int signo, void (*func)(int))
{
    if(signo < 1 || signo > 63)
    {
        LOGGING_ERROR("No this signal");
        return -1;
    }
    this->m_sighandle_map[signo] = func;
    return 0;
}

int HVN::Signal_manager::start(void)
{
    sigset_t bset, oset;
    sigemptyset(&bset);
    sigemptyset(&oset);
    for(std::map<int, void (*)(int)>::iterator it = this->m_sighandle_map.begin(); it != this->m_sighandle_map.end(); it++)
        sigaddset(&bset, it->first);
    if(pthread_sigmask(SIG_BLOCK, &bset, &oset) != 0)
    {
        LOGGING_ERROR("pthread_sigmask");
        return -1;
    }
    if(this->m_signal_thread.start(1))
    {
        LOGGING_ERROR("start signal handler thread error");
        return -1;
    }
    return 0;
}

void HVN::Signal_manager::Signal_thread::work_function(void)
{
    int signo = 0;
    sigset_t sigset;
    sigemptyset(&sigset);
    for(std::map<int, void (*)(int)>::iterator it = this->m_sighandle_map.begin(); it != this->m_sighandle_map.end(); it++)
        sigaddset(&sigset, it->first);
    while(1)
    {
        if(sigwait(&sigset, &signo))
        {
            LOGGING_ERROR("sigwait return an error");
            std::exit(-1);
        }
        if(this->m_sighandle_map[signo] == NULL)
        {
            LOGGING_INFO("ignore the signal");
            continue;
        }
        (this->m_sighandle_map[signo])(signo);
    }
}


