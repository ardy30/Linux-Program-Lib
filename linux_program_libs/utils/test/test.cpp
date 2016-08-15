/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 18:11:19
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

#include "../utils.h"

int main()
{

    HVN::Time t1(1), t2(2);
    std::cout << (t2 == t1) << std::endl;
    std::cout << (t2 != t1) << std::endl;
    std::cout << (t1 <= t1) << std::endl;
    std::cout << (t2 >= t1) << std::endl;
    std::cout << (t2 > t1) << std::endl;
    std::cout << (t2 < t1) << std::endl;

/*
    std::cout << (t2 + t1).get_nsec() << std::endl;
    t2 += t1;
    std::cout << t2.get_nsec() << std::endl;
    t1.now(HVN::Time::Monotonic);
    sleep(2);
    t2.now(HVN::Time::Monotonic);
    std::cout << (t2 - t1).get_nsec() << std::endl;
*/  
/*
    struct timeb tb;
    struct timeval tv;
    struct timespec ts;
    std::cout << t.get_nsec() << std::endl;

    tb = t.to_timeb();
    tv = t.to_timeval();
    ts = t.to_timespec();
    sleep(3);
    t.now(HVN::Time::Monotonic);
    std::cout << t.get_nsec() << std::endl;
    t.set(tb);
    std::cout << t.get_nsec() << std::endl;
    t.set(tv);
    std::cout << t.get_nsec() << std::endl;
    t.set(ts);
    std::cout << t.get_nsec() << std::endl;
    t.set(3);
    std::cout << t.get_nsec() << std::endl;
*/
/*
    std::cout << tb.time << std::endl;
    std::cout << tb.millitm << std::endl;
    std::cout << tv.tv_sec << std::endl;
    std::cout << tv.tv_usec << std::endl;
    std::cout << ts.tv_sec << std::endl;
    std::cout << ts.tv_nsec << std::endl;
    std::cout << t.get_sec() << std::endl;
    std::cout << t.get_msec() << std::endl;
    std::cout << t.get_usec() << std::endl;
    std::cout << t.get_nsec() << std::endl;
*/
/*
    std::cout << t.get_date_local_string() << std::endl;
    std::cout << t.get_date_string() << std::endl;
    std::cout << t.get_date_year() << std::endl;
    std::cout << t.get_date_local_year() << std::endl;
    std::cout << t.get_date_month() << std::endl;
    std::cout << t.get_date_local_month() << std::endl;
    std::cout << t.get_date_day() << std::endl;
    std::cout << t.get_date_local_day() << std::endl;
    std::cout << t.get_date_hour() << std::endl;
    std::cout << t.get_date_local_hour() << std::endl;
    std::cout << t.get_date_minite() << std::endl;
    std::cout << t.get_date_local_minite() << std::endl;
    std::cout << t.get_date_second() << std::endl;
    std::cout << t.get_date_local_second() << std::endl;
    std::cout << t.get_date_wday() << std::endl;
    std::cout << t.get_date_local_wday() << std::endl;
    std::cout << t.get_date_yday() << std::endl;
    std::cout << t.get_date_local_yday() << std::endl;
*/
/*
    try
    {
        throw SYSCALL_EXCEPTION("haha");
    } 
    catch(HVN::Syscall_exception &e)
    {
        std::cout << e << std::endl;
    }
*/
    return 0;
}

