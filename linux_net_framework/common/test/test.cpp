/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/12/11 21:44:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <iostream>
#include "../Resource_factory.h"

class A
{
public:
    void recycle(void)
    {
        std::cout << "hahaa" << std::endl;
    }
};

class B
{
public:
    void recycle(void)
    {
        std::cout << "hahab" << std::endl;
    }
};

int main()
{
    A *pa = Resource_factory<A>::get_pinstance()->new_resource();
    Resource_factory<A>::get_pinstance()->recycle(pa);

    B *pb = Resource_factory<B>::get_pinstance()->new_resource();
    Resource_factory<B>::get_pinstance()->recycle(pb);

    return 0;
}

