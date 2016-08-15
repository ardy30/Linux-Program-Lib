#ifndef __MAIN_BODY_H__
#define __MAIN_BODY_H__

#include "linux_program_libs/utils/Singleton.h"
#include "linux_program_libs/pthread/Thread.h"
#include "linux_program_libs/pthread/Mutex_Cond.h"

class Main_body: public HVN::Singleton<Main_body>
{
    class Main_thread: public HVN::Thread
    {
    public:
        Main_thread(Main_body *pMain_body): HVN::Thread(), m_pMain_body(pMain_body) {}
    
    public:
        virtual void work_function(void);

    private:
        Main_body *m_pMain_body;
    };

private:
    friend class HVN::Singleton<Main_body>;
    Main_body(void): m_main_thread(this) {}

public:
    int initial(void);

private:
    int app_init(void);

private:
    friend class Main_thread;
    Main_thread m_main_thread;
    HVN::Event m_event;
};

#endif

