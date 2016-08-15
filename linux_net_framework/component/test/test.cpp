/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/14/11 11:54:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include "../Basic_config_manager.h"
#include "../Work_item.h"

class A
{
public:
    int h(int a, int b)
    {
        std::cout << a + b << std::endl;
        return 0;
    }

    std::tr1::function<int (void)> b()
    {
        return std::tr1::bind(&A::h, this, 4, 6);
    }
};

int main(int argc, char **argv)
{
/*
    Basic_config_manager::get_pinstance()->initial(argv[1]);
    Basic_config_manager::get_pinstance()->show_config();
*/
    A a;
    std::tr1::function<int ()> haha = a.b();
    haha();

    return 0;
}

