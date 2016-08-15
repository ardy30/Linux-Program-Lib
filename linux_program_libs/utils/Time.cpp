/*
 * =====================================================================================
 *
 *       Filename:  Time.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/20/11 22:59:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <errno.h>
#include <cstring>
#include "Time.h"
#include "../log/log.h"

uint64_t HVN::Time::now(Clock_type type)
{
    if(type == Realtime)
    {
        struct timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts))
            LOGGING_ERROR(std::strerror(errno));
        this->m_nsec = ts.tv_sec * 1000000000 + ts.tv_nsec;
        return this->m_nsec;
    }
    else
    {
        struct timespec ts;
        if(clock_gettime(CLOCK_MONOTONIC, &ts))
            LOGGING_ERROR(std::strerror(errno));
        this->m_nsec = ts.tv_sec * 1000000000 + ts.tv_nsec;
        return this->m_nsec;
    }
}

int HVN::Time::get_date_year(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return 1900 + tms.tm_year;
}

int HVN::Time::get_date_local_year(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return 1900 + tms.tm_year;
}

int HVN::Time::get_date_month(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return 1 + tms.tm_mon;
}

int HVN::Time::get_date_local_month(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return 1 + tms.tm_mon;
}

int HVN::Time::get_date_day(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return tms.tm_mday;
}

int HVN::Time::get_date_local_day(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return tms.tm_mday;
}

int HVN::Time::get_date_hour(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return tms.tm_hour;
}

int HVN::Time::get_date_local_hour(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return tms.tm_hour;
}

int HVN::Time::get_date_minite(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return tms.tm_min;
}

int HVN::Time::get_date_local_minite(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return tms.tm_min;
}

int HVN::Time::get_date_second(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return tms.tm_sec;
}

int HVN::Time::get_date_local_second(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return tms.tm_sec;
}

int HVN::Time::get_date_wday(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return tms.tm_wday;
}

int HVN::Time::get_date_local_wday(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return tms.tm_wday;
}

int HVN::Time::get_date_yday(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    return 1 + tms.tm_yday;
}

int HVN::Time::get_date_local_yday(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    return 1 + tms.tm_yday;
}


std::string HVN::Time::get_date_string(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    gmtime_r(&sec, &tms);
    char buf[256];
    asctime_r(&tms, buf);
    buf[std::strlen(buf) - 1] = '\0';
    return std::string(buf);
}

std::string HVN::Time::get_date_local_string(void) const
{
    time_t sec = this->get_sec();
    struct tm tms;
    localtime_r(&sec, &tms);
    char buf[256];
    asctime_r(&tms, buf);
    buf[std::strlen(buf) - 1] = '\0';
    return std::string(buf); 
}


