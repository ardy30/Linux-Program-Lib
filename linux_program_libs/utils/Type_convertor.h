/*
 * =====================================================================================
 *
 *       Filename:  Type_convertor.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 15:29:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_TYPE_CONVERTOR_H__
#define __HVN_TYPE_CONVERTOR_H__

#include <sstream>

namespace HVN
{

template <typename ST, typename DT>
class Type_convertor
{
public:
    static DT conv(const ST &s)
    {
        std::stringstream ss;
        ss << s;
        DT d;
        ss >> d;
        return d;
    }
};

} // namespace HVN

#endif

