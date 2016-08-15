/*
 * =====================================================================================
 *
 *       Filename:  Handle_log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 19:39:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_HANDLE_LOG_H__
#define __HVN_HANDLE_LOG_H__

#include "../utils/Singleton.h"

namespace HVN
{

class Logger;

class Handle_log: public Singleton<Handle_log>
{
private:
    friend class Singleton<Handle_log>;
    Handle_log(void);

public:
    void set_log_level(int log_level);
    void log_trace(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const;
    void log_info(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const;
    void log_warn(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const;
    void log_error(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const;
    void log_fatal(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const;

private:
    int m_log_level;
    Logger *m_logger;
};

} //namespace HVN

#endif


