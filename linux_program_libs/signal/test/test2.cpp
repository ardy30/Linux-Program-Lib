/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/11 22:02:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <cstring>
#include "../Signal_manager.h"
#include "../../utils/Time.h"

void handle_signal(int signo)
{
    std::cout << signo << std::endl;
}


int main()
{
    HVN::Signal_manager::get_pinstance()->register_signal(SIGQUIT, NULL);
//    HVN::Signal_manager::get_pinstance()->register_signal(SIGINT, handle_signal);
    HVN::Signal_manager::get_pinstance()->register_signal(SIGALRM, handle_signal);
    HVN::Signal_manager::get_pinstance()->register_signal(SIGVTALRM, handle_signal);
    HVN::Signal_manager::get_pinstance()->register_signal(SIGPROF, handle_signal);
    HVN::Signal_manager::get_pinstance()->start();

    HVN::Time t1(0);
    HVN::Time t2(1000000000);
    itimerval value, ovalue;
    value.it_interval = t1.to_timeval();
    value.it_value = t2.to_timeval();
    setitimer(ITIMER_PROF, &value, &ovalue);    

    while(1);
    //sleep(10);
    return 0;
}















