#ifndef __PERSIST_TIMER_TASK_H__
#define __PERSIST_TIMER_TASK_H__

#include <string>
#include "../common/Task.h"
#include "../common/Timer.h"

class Persist_timer_task: public Task
{
public:
    Persist_timer_task(void);

public:
    virtual int initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj);

private:
    void persist_timer_cb(Timer *ptimer);
    Timer *m_ptimer;
};

#endif

