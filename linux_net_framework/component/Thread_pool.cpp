#include <errno.h>
#include <cstring>
#include "../../linux_program_libs/log/log.h"
#include "Thread_pool.h"
#include "Work_item.h"

void Thread_pool::initial(int nr_thread, int sock)
{
    this->m_nr_thread = nr_thread;
    this->m_sock = sock;
}

int Thread_pool::run(void)
{
    if(this->m_nr_thread <= 0 || this->m_sock == -1)
    {
        LOGGING_ERROR("thread pool args init error");
        return -1;
    }
    for(int i = 0; i < this->m_nr_thread; i++)
    {
        Work_thread *pwork_thread = new Work_thread(this->m_sock);
        if(pwork_thread->start(1) == -1)
        {
            LOGGING_ERROR("pthread_create");
            return -1;
        }
        this->m_thread_list.push_back(pwork_thread);
    }
    return 0;
}

void Thread_pool::Work_thread::work_function(void)
{
    while(1)
    {
        int ret = 0;
        Work_item *pwork_item = NULL;
        ret = read(this->m_sock, (char *)&pwork_item, sizeof(pwork_item));
        if(ret <= 0)
            LOGGING_FATAL(std::strerror(errno));
        pwork_item->process();
        ret = write(this->m_sock, (char *)&pwork_item, sizeof(pwork_item));
        if(ret != sizeof(pwork_item))
            LOGGING_FATAL(std::strerror(errno));
    }
}

