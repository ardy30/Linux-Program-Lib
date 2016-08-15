/*
 * =====================================================================================
 *
 *       Filename:  test2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/09/11 22:55:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include "../Sock_addr_v4.h"
#include "../Tcp_v4_socket.h"

int main()
{
    HVN::Sock_addr_v4 servsa;
    servsa.set_ip("192.168.1.49");
    servsa.set_port(65432);
    HVN::Tcp_v4_socket so;
    if(so.init_sock() || so.set_keep_alive() || so.unset_linger() || so.unset_nagle())
        std::cout << "init error" << std::endl;
    if(so.connect_sock(servsa))
        std::cout << "connect error" << std::endl;
    int n = so.write_sock("haha", 4);
    char buf[64];
    int m = so.readn_sock(buf, n);
    buf[m] = '\0';
    std::cout << buf << std::endl;
    return 0;
}

