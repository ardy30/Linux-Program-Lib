#include "Scheduler.h"
#include "../../linux_program_libs/log/log.h"

Scheduler::~Scheduler(void)
{
    if(this->m_eb)
        event_base_free(this->m_eb);
}

event_base *Scheduler::get_base(void) const
{
    return this->m_eb;
}

int Scheduler::initial(void)
{
    this->m_eb = event_base_new();
    if(!this->m_eb)
    {
        LOGGING_FATAL("event_base_new");
        return -1;
    }
    return 0;
}

int Scheduler::run(void) const
{
    return event_base_dispatch(this->m_eb);
}

