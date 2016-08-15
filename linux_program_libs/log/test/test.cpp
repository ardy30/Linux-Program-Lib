/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/11 18:11:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <iostream>

#include "../log.h"

int main()
{

    for(int i = 0; i < 9; i++)
    {
        LOGGING_LEVEL(i);
        LOGGING_TRACE("huhu");
        LOGGING_INFO("kkk");
        LOGGING_WARN("sss");
        LOGGING_ERROR("ssxxx");
        LOGGING_FATAL("ssccccc");
    }

    return 0;
}

