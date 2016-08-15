/*
 * =====================================================================================
 *
 *       Filename:  Console_logger.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 00:08:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_CONSOLE_LOGGER_H__
#define __HVN_CONSOLE_LOGGER_H__

#include "Logger.h"

namespace HVN
{

class Console_logger: public Logger
{
public:
    explicit Console_logger(void *arg);

public:
    virtual void logger_trace(const char *buf_str, const char *file_str, const char *function_str, const int line_nr);
    virtual void logger_info(const char *buf_str, const char *file_str, const char *function_str, const int line_nr);
    virtual void logger_warn(const char *buf_str, const char *file_str, const char *function_str, const int line_nr);
    virtual void logger_error(const char *buf_str, const char *file_str, const char *function_str, const int line_nr);
    virtual void logger_fatal(const char *buf_str, const char *file_str, const char *function_str, const int line_nr);
};

} //namespace HVN

#endif

