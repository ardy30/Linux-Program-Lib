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

void handle_signal(int signo)
{
    std::cout << signo << std::endl;
}

void handle_pipe_signal(int signo)
{
    std::cout << "pipe " << errno << std::endl;
}

int main()
{
    HVN::Signal_manager::get_pinstance()->register_signal(SIGQUIT, NULL);
//    HVN::Signal_manager::get_pinstance()->register_signal(SIGINT, handle_signal);
//    HVN::Signal_manager::get_pinstance()->register_signal(SIGPIPE, handle_pipe_signal);
    HVN::Signal_manager::get_pinstance()->start();
    
    signal(SIGPIPE, handle_pipe_signal);

    int fd[2];
    pipe(fd);
    char buf[4096];
    for(int i = 0; i < 100; i++)
    {
        int n = write(fd[1], buf, 4096);
        std::cout << n << std::endl;
        std::cout << std::strerror(errno) << std::endl;
        std::cout << i << std::endl;
    }

    sleep(10);
    return 0;
}















