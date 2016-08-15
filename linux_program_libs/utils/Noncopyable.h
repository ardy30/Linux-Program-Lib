/*
 * =====================================================================================
 *
 *       Filename:  Noncopyable.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/15/11 17:43:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_NONCOPYABLE_H__
#define __HVN_NONCOPYABLE_H__

namespace HVN
{

class Noncopyable
{
protected:
    Noncopyable(void) {}
    virtual ~Noncopyable(void) {}

private:
    Noncopyable(const Noncopyable &nc);
    Noncopyable& operator=(const Noncopyable &nc);
};

} //namespace HVN

#endif

