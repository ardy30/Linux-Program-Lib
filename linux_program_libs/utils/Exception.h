/*
 * =====================================================================================
 *
 *       Filename:  Exception.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 23:38:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_EXCEPTION_H__
#define __HVN_EXCEPTION_H__

#include <exception>
#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include "Type_convertor.h"

namespace HVN
{

class Exception: public std::exception
{
public:
    Exception(const std::string &exstr, const std::string &file, const std::string &func, const int line):
        m_exstr(exstr), m_file(file), m_func(func), m_line(line) {}
    ~Exception(void) throw() {}
        
public:
    const char* what(void) const throw()
    {
        try {
            this->m_message.clear();
            this->m_message += "Exception: " + this->m_exstr + ", File: " + this->m_file + ", Func: " + this->m_func 
                             + ", Line: " + Type_convertor<int, std::string>::conv(this->m_line);
            return this->m_message.c_str();
        } catch(...) { return ""; }
    }

protected:
    std::string m_exstr;
    std::string m_file;
    std::string m_func;
    int m_line;
    mutable std::string m_message;
};

class Syscall_exception: public Exception
{
public:
    Syscall_exception(const std::string &exstr, const std::string &file, const std::string &func, const int line):
        Exception(exstr, file, func, line), m_errno(errno) {}
    ~Syscall_exception(void) throw() {}

public:
    int get_errno(void)
    { return this->m_errno; }
    const char* what(void) const throw()
    {
        try {
            this->m_message.clear();
            this->m_message += "Syscall_exception: " + this->m_exstr + ", File: " + this->m_file + ", Func: " + this->m_func
                             + ", Line: " + Type_convertor<int, std::string>::conv(this->m_line) + ", Error: " + std::strerror(this->m_errno);
            return this->m_message.c_str();
        } catch(...) { return ""; }
    }

private:
    int m_errno;
};

} //namespace HVN

inline std::ostream &operator<<(std::ostream &os, HVN::Exception &e)
{ os << e.what(); return os; }

#define EXCEPTION(str)              HVN::Exception(str, __FILE__, __FUNCTION__, __LINE__)
#define SYSCALL_EXCEPTION(str)      HVN::Syscall_exception(str, __FILE__, __FUNCTION__, __LINE__)

#endif

