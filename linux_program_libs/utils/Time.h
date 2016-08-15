/*
 * =====================================================================================
 *
 *       Filename:  Time.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/17/11 19:27:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_TIME_H__
#define __HVN_TIME_H__

#include <sys/types.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <ctime>
#include <string>

namespace HVN
{

class Time
{
private:
    enum Clock_type { Realtime, Monotonic };

public:
    Time(uint64_t nsec = 0): m_nsec(nsec) {}
    Time(timeb &tb) { this->m_nsec = tb.time * 1000000000 + tb.millitm * 1000000; }
    Time(timeval &tv) { this->m_nsec = tv.tv_sec * 1000000000 + tv.tv_usec * 1000; }
    Time(timespec &ts) { this->m_nsec = ts.tv_sec * 1000000000 + ts.tv_nsec; }

public:
    void set(uint64_t nsec = 0) { this->m_nsec = nsec; }
    void set(timeb &tb) { this->m_nsec = tb.time * 1000000000 + tb.millitm * 1000000; }
    void set(timeval &tv) { this->m_nsec = tv.tv_sec * 1000000000 + tv.tv_usec * 1000; }
    void set(timespec &ts) { this->m_nsec = ts.tv_sec * 1000000000 + ts.tv_nsec; }

    uint64_t to_uint64_t(void) const 
    { return this->m_nsec; }
    timeb to_timeb(void) const 
    { struct timeb tb; uint64_t msec = this->m_nsec / 1000000; tb.time = msec / 1000; tb.millitm = msec % 1000; return tb; }
    timeval to_timeval(void) const
    { struct timeval tv; uint64_t usec = this->m_nsec / 1000; tv.tv_sec = usec / 1000000; tv.tv_usec = usec % 1000000; return tv; }
    timespec to_timespec(void) const
    { struct timespec ts; ts.tv_sec = this->m_nsec / 1000000000; ts.tv_nsec = this->m_nsec % 1000000000; return ts; }

public:
    uint64_t get_sec(void) const { return this->m_nsec / 1000000000; }
    uint64_t get_msec(void) const { return this->m_nsec / 1000000; }
    uint64_t get_usec(void) const { return this->m_nsec / 1000; }
    uint64_t get_nsec(void) const { return this->m_nsec; }

public:
    uint64_t now(Clock_type type = Realtime);
    int get_date_year(void) const;
    int get_date_local_year(void) const;
    int get_date_month(void) const;
    int get_date_local_month(void) const; 
    int get_date_day(void) const;
    int get_date_local_day(void) const;
    int get_date_hour(void) const;
    int get_date_local_hour(void) const;
    int get_date_minite(void) const;
    int get_date_local_minite(void) const;
    int get_date_second(void) const;
    int get_date_local_second(void) const;
    int get_date_wday(void) const;
    int get_date_local_wday(void) const;
    int get_date_yday(void) const;
    int get_date_local_yday(void) const;
    std::string get_date_string(void) const;
    std::string get_date_local_string(void) const;

public:
    Time operator-(Time &rht) const { return Time(this->m_nsec - rht.m_nsec); }
    Time operator+(Time &rht) const { return Time(this->m_nsec + rht.m_nsec); }
    Time &operator-=(Time &rht) { this->m_nsec -= rht.m_nsec; return *this; }
    Time &operator+=(Time &rht) { this->m_nsec += rht.m_nsec; return *this; }
    bool operator<(Time &rht) const { return this->m_nsec < rht.m_nsec; }
    bool operator<=(Time &rht) const { return this->m_nsec <= rht.m_nsec; }
    bool operator>(Time &rht) const { return this->m_nsec > rht.m_nsec; }
    bool operator>=(Time &rht) const { return this->m_nsec >= rht.m_nsec; }
    bool operator==(Time &rht) const { return this->m_nsec == rht.m_nsec; }
    bool operator!=(Time &rht) const { return this->m_nsec != rht.m_nsec; }

private:
    uint64_t m_nsec;
};


} //namespace HVN

#endif

