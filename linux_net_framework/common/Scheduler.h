#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <event2/event.h>
#include "../../linux_program_libs/utils/Singleton.h"

class Scheduler: public HVN::Singleton<Scheduler>
{
private:
    friend class HVN::Singleton<Scheduler>;
    Scheduler(void): m_eb(NULL) {}

public:
    ~Scheduler(void);

public:
    int initial(void);
    int run(void) const;
    event_base *get_base(void) const;

private:
    event_base *m_eb;
};

#endif

