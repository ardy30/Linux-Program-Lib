#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <list>
#include "../../linux_program_libs/pthread/Thread.h"

class Thread_pool
{
    class Work_thread: public HVN::Thread
    {
    private:
        friend class Thread_pool;
        Work_thread(int sock): HVN::Thread(), m_sock(sock) {}
    
    protected:
        virtual void work_function(void);

    private:
        int m_sock;
    };

public:
	Thread_pool(void): m_nr_thread(2), m_sock(-1) {}

public:
	void initial(int nr_thread, int sock);
	int run(void);

private:
	int m_nr_thread;
	int m_sock;
	std::list<Work_thread *> m_thread_list;
};

#endif

