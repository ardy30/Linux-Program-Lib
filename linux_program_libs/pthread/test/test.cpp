/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/11 12:17:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <iostream>
#include "../Thread.h"
#include "../Mutex_Cond.h"

#if 0

class Test_thread: public HVN::Thread
{
public:
    Test_thread(void): HVN::Thread(), m_count(0) {}

protected:
    virtual void work_function(void)
    {
//        while(1);
        for(;;)
        {
            std::cout << "haha" << std::endl;
            sleep(1);
            if(this->m_count++ == 5)
                return;
        }
    }
    int get_count(void)
    {
        return this->m_count;
    }
private:
    int m_count;
};

int main()
{
/* 
    Test_thread tt;
//    tt.start(1);
    tt.start();
    std::cout << tt.get_tid() << std::endl;
    std::cout << tt.is_active() << std::endl;
    tt.join();
    std::cout << tt.is_active() << std::endl;
    std::cout << "main thread" << std::endl;
*/
/*
    Test_thread tt1, tt2, tt3;
    tt1.start();
    tt1.start();
    tt2.start();
    tt3.start();
    std::cout << tt1.get_tid() << std::endl; 
    std::cout << tt2.get_tid() << std::endl; 
    std::cout << tt3.get_tid() << std::endl; 
*/
/*
    Test_thread tt;
//    tt.start(1, 0, 1, 0);
//    tt.start(1, 0, 1, 1);
    tt.start(1, 0, 0);
    sleep(2);
    tt.cancel();
    std::cout << "canceled" << std::endl;
    sleep(9);
    std::cout << "main thread" << std::endl;
    std::cout << tt.get_count() << std::endl;
*/


    return 0;
}

#endif


HVN::Mutex mt;
HVN::Event ev;
//HVN::Mutex mt(1);
HVN::Cond cd(mt);

class Test_thread: public HVN::Thread
{
public:
    virtual void work_function(void)
    {
        sleep(4);
        ev.notify();
    }
};


void func(void)
{
    HVN::Mutex_lock lock(mt);
    HVN::Time tm(3000000000);
    cd.rel_timed_wait(tm);
}

int main()
{
/*
    HVN::Mutex_lock lock1(mt);
    HVN::Mutex_lock lock2(mt);
    std::cout << "never" << std::endl;
*/
/*
    Test_thread tt;
    tt.start(1);
    ev.wait();
    std::cout << "haha" << std::endl;
*/

    func();

    return 0;
}

