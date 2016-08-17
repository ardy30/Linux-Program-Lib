#include <cstdlib>
#include "../linux_program_libs/log/log.h"
#include "../linux_program_libs/net/Tcp_v4_socket.h"
#include "../linux_net_framework/common/Scheduler.h"
#include "../linux_net_framework/common/Task_factory.h"
#include "../linux_net_framework/component/Basic_config_manager.h"
#include "../linux_net_framework/component/Persist_timer_task.h"
#include "../linux_net_framework/component/Middle_server_task.h"
#include "../linux_net_framework/component/Thread_pool.h"
#include "Main_body.h"
#include "Echo_listen_task.h"

Thread_pool g_thread_pool;

void Main_body::Main_thread::work_function(void)
{
    if(Scheduler::get_pinstance()->initial())
    {
        LOGGING_FATAL("sched init error");
        std::exit(-1);
    }
    
    Persist_timer_task *ppersist_timer_task = Task_factory::get_pinstance()->new_task<Persist_timer_task>();
    if(ppersist_timer_task->initial(NULL, NULL))
    {
        LOGGING_FATAL("ppersist_timer_task init error");
        std::exit(-1);
    }

    g_pmiddle_server_task = Task_factory::get_pinstance()->new_task<Middle_server_task>();
    if(g_pmiddle_server_task->initial(NULL, NULL))
    {
        LOGGING_FATAL("g_pmiddle_server_task init error");
        std::exit(-1);
    }
    
    this->m_pMain_body->m_event.notify();

    if(this->m_pMain_body->app_init())
    {
        LOGGING_FATAL("application init error");
        std::exit(-1);
    }

    Scheduler::get_pinstance()->run();
}

int Main_body::app_init()
{
    // TODO:
    Echo_listen_task *pecho_listen_task = Task_factory::get_pinstance()->new_task<Echo_listen_task>();
    if(pecho_listen_task->initial(NULL, NULL))
    {
        LOGGING_FATAL("pecho_listen_task->initial");
        std::exit(-1);
    }
    return 0;
}

int Main_body::initial()
{
    if(this->m_main_thread.start(1))
    {
        LOGGING_FATAL("main thread start error");
        std::exit(-1);
    }

    this->m_event.wait();

    HVN::Sock_addr_v4 middle_server_sa;
    middle_server_sa.set_ip(Basic_config_manager::get_pinstance()->get_localhost_ip());
    middle_server_sa.set_port(Basic_config_manager::get_pinstance()->get_middle_server_port());
    HVN::Tcp_v4_socket middle_server_sock;
    if(middle_server_sock.init_sock() || middle_server_sock.connect_sock(middle_server_sa))
    {
        LOGGING_FATAL("connect middle server error");
        std::exit(-1);
    }

    g_thread_pool.initial(Basic_config_manager::get_pinstance()->get_thread_pool_nr(), middle_server_sock.get_fd());
    g_thread_pool.run();

    LOGGING_INFO("Main_body Init OK");
    return 0;
}

