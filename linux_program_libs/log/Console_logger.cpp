/*
 * =====================================================================================
 *
 *       Filename:  Console_logger.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 00:12:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <sstream>

#include "../utils/Time.h"
#include "Console_logger.h"
#include "color_print.h"

HVN::Console_logger::Console_logger(void *arg):
    Logger(arg)
{}

void HVN::Console_logger::logger_trace(const char *buf_str, const char *file_str, const char *function_str, const int line_nr)
{
    Time tm;
    tm.now();
    std::stringstream ss; 
    ss << tm.get_date_string() << "....trace(file: " << file_str << ", func: " << function_str << ", line: " << line_nr << "): " << buf_str;
    WHITE_MSG(ss.str().c_str());
}

void HVN::Console_logger::logger_info(const char *buf_str, const char *file_str, const char *function_str, const int line_nr)
{
    Time tm;
    tm.now();
    std::stringstream ss;
    ss << tm.get_date_string() << "....info (file: " << file_str << ", func: " << function_str << ", line: " << line_nr << "): " << buf_str;  
    GREEN_MSG(ss.str().c_str());
}

void HVN::Console_logger::logger_warn(const char *buf_str, const char *file_str, const char *function_str, const int line_nr)
{
    Time tm;
    tm.now(); 
    std::stringstream ss; 
    ss << tm.get_date_string() << "....warn (file: " << file_str << ", func: " << function_str << ", line: " << line_nr << "): " << buf_str;
    BLUE_MSG(ss.str().c_str());
}

void HVN::Console_logger::logger_error(const char *buf_str, const char *file_str, const char *function_str, const int line_nr)
{
    Time tm;
    tm.now();
    std::stringstream ss;
    ss << tm.get_date_string() << "....error(file: " << file_str << ", func: " << function_str << ", line: " << line_nr << "): " << buf_str;
    YELLOW_MSG(ss.str().c_str());
}

void HVN::Console_logger::logger_fatal(const char *buf_str, const char *file_str, const char *function_str, const int line_nr)
{
    Time tm;
    tm.now();
    std::stringstream ss;
    ss << tm.get_date_string() << "....fatal(file: " << file_str << ", func: " << function_str << ", line: " << line_nr << "): " << buf_str; 
    RED_MSG(ss.str().c_str());
}

