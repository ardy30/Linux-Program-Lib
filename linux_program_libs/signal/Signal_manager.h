/*
 * =====================================================================================
 *
 *       Filename:  Signal_manager.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/11 22:14:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_SIGNAL_MANAGER_H__
#define __HVN_SIGNAL_MANAGER_H__

#include <signal.h>
#include <map>
#include "../pthread/Thread.h"
#include "../utils/Singleton.h"

namespace HVN
{

class Signal_manager: public Singleton<Signal_manager>
{
    class Signal_thread: public Thread
    {
    public:
        explicit Signal_thread(std::map<int, void (*)(int)> &sighandle_map): Thread(), m_sighandle_map(sighandle_map) {}

    protected:
        virtual void work_function(void);

    private:
        std::map<int, void (*)(int)> &m_sighandle_map;
    };
private:
    friend class Singleton<Signal_manager>;
    Signal_manager(void): m_sighandle_map(), m_signal_thread(m_sighandle_map) {}

public:
    int register_signal(int signo, void (*func)(int));
    int start(void);

private:
    std::map<int, void (*)(int)> m_sighandle_map;
    Signal_thread m_signal_thread;
};

} // namespace HVN


#endif

