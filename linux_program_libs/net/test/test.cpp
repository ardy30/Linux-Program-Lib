/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/08/11 23:16:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <iostream>
#include "../Sock_addr_v4.h"
#include "../Tcp_v4_socket.h"

int main()
{
/*
    HVN::Sock_addr_v4 sa_v4;
    sa_v4.set_by_sockaddr_in(sa_v4.get_sockaddr_in());
    std::cout << sa_v4 << std::endl;
*/
    HVN::Sock_addr_v4 sa_v4;
    sa_v4.set_ip("0.0.0.0");
    sa_v4.set_port(65432);

    HVN::Tcp_v4_socket tso;
    if(tso.init_sock() || tso.set_reuse_addr() || tso.bind_sock(sa_v4) || tso.listen_sock(5))
        std::cout << "init error" << std::endl;

    char buf[1024];
    int readn;
    HVN::Sock_addr_v4 clisa;
    int fd = tso.accept_sock(clisa);
    std::cout << clisa << std::endl;
    HVN::Tcp_v4_socket cliso(fd);
    HVN::Sock_addr_v4 tempsa;
    cliso.get_peer_addr(tempsa);
    std::cout << tempsa << std::endl;
    cliso.get_local_addr(tempsa);
    std::cout << tempsa << std::endl;
    while(readn = cliso.read_sock(buf, 1024))
        cliso.writen_sock(buf, readn);
    cliso.close_sock();
    tso.close_sock();
    return 0;
}

