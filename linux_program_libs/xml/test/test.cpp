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

#include "../Xml.h"

int main()
{
    HVN::Xml xml;
    std::string str_buf;
    xml.save_in_buffer(xml.load_from_file("./config.xml"), str_buf);
    std::cout << str_buf << std::endl;

    return 0;
}

