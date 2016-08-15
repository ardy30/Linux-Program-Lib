#ifndef __WORK_ITEM_H__
#define __WORK_ITEM_H__

#include <tr1/functional>
#include "../common/Task.h"

class Work_item
{
public:
	Work_item(Task *ptask, std::tr1::function<int (void *)> work_fn_obj, void *arg, std::tr1::function<void (int, void *)> reply_fn_obj):
        m_work_fn_obj(work_fn_obj), m_arg(arg), m_reply_fn_obj(reply_fn_obj), m_success(0), m_ptask(ptask) 
    { this->m_ptask->inc_nr_req(); }
	~Work_item(void)
    { this->m_ptask->dec_nr_req(); }

public:
	void process(void)
    { this->m_success = this->m_work_fn_obj(this->m_arg); }
	void reply(void)
    {
        if(this->m_ptask->is_recycled())
            return;
        this->m_reply_fn_obj(this->m_success, this->m_arg); 
    }

private:
    std::tr1::function<int (void *)> m_work_fn_obj;
    void *m_arg;
    std::tr1::function<void (int, void *)> m_reply_fn_obj;
	int m_success;
	Task *m_ptask;
};

#endif

