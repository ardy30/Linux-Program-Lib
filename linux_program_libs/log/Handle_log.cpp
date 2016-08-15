/*
 * =====================================================================================
 *
 *       Filename:  Handle_log.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 23:59:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include "Handle_log.h"
#include "Logger.h"
#include "Console_logger.h"

HVN::Handle_log::Handle_log(void):
    m_log_level(0)
{
    this->m_logger = new Console_logger(NULL);
}

void HVN::Handle_log::set_log_level(int log_level)
{
    if(log_level < 0)
        log_level = 0;
    if(log_level > 5)
        log_level = 5;
    this->m_log_level = log_level;
}

void HVN::Handle_log::log_trace(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const
{
    switch(this->m_log_level)
    {
    case 0:
        this->m_logger->logger_trace(buf_str, file_str, function_str, line_nr);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    }
}
    
void HVN::Handle_log::log_info(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const
{
    switch(this->m_log_level)
    {
    case 0:
    case 1:
        this->m_logger->logger_info(buf_str, file_str, function_str, line_nr);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    }
}

void HVN::Handle_log::log_warn(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const
{
    switch(this->m_log_level)
    {
    case 0:
    case 1:
    case 2:
        this->m_logger->logger_warn(buf_str, file_str, function_str, line_nr);
        break;
    case 3:
    case 4:
    case 5:
        break;
    }
}
    
void HVN::Handle_log::log_error(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const
{
    switch(this->m_log_level)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        this->m_logger->logger_error(buf_str, file_str, function_str, line_nr);
        break;
    case 4:
    case 5:
        break;
    }
}
    
void HVN::Handle_log::log_fatal(const char *buf_str, const char *file_str, const char *function_str, const int line_nr) const
{
    switch(this->m_log_level)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        this->m_logger->logger_fatal(buf_str, file_str, function_str, line_nr);  
        break;
    case 5:
        break;
    }
}


