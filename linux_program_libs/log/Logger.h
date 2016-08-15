/*
 * =====================================================================================
 *
 *       Filename:  Logger.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 23:52:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_LOGGER_H__
#define __HVN_LOGGER_H__

#include "../utils/Noncopyable.h"

namespace HVN
{

class Logger: public Noncopyable
{
public:
    explicit Logger(void *arg) {};
    virtual ~Logger(void) {};

public:
    virtual void logger_trace(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) = 0;
    virtual void logger_info(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) = 0;
    virtual void logger_warn(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) = 0;
    virtual void logger_error(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) = 0;
    virtual void logger_fatal(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) = 0;
};

} //namespace HVN

#endif

