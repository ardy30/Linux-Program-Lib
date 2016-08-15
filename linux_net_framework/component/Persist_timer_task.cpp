#include <tr1/functional>
#include "../../linux_program_libs/log/log.h"
#include "../common/Task_factory.h"
#include "Persist_timer_task.h"
#include "Basic_config_manager.h"

Persist_timer_task::Persist_timer_task(void):
    m_ptimer(NULL)
{
    m_task_type = 0;
    m_task_discribe = "persist timer task";
}

int Persist_timer_task::initial(void *arg, std::tr1::function<void (Task *, int, void *)> result_cb_obj)
{
    this->m_ptimer = this->open_timer();
    if(this->m_ptimer->initial(this, 1, std::tr1::bind(&Persist_timer_task::persist_timer_cb, this, std::tr1::placeholders::_1)))
    {
        LOGGING_ERROR("Persist_timer_task::initial - initial");
        return -1;
    }
    HVN::Time timer_tv(Basic_config_manager::get_pinstance()->get_persist_timeout() * 1000000000l);
    this->m_ptimer->begin(timer_tv);
    return 0;
}

void Persist_timer_task::persist_timer_cb(Timer *ptimer)
{
    Task_factory::get_pinstance()->clear_recycle();
    LOGGING_INFO("persist timer");
}

