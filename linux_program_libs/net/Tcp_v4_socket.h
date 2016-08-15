/*
 * =====================================================================================
 *
 *       Filename:  Tcp_v4_socket.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/09/11 00:16:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#ifndef __HVN_TCP_V4_SOCKET_H__
#define __HVN_TCP_V4_SOCKET_H__

#include "../utils/Noncopyable.h"
#include "Sock_addr_v4.h"

namespace HVN
{

class Tcp_v4_socket: public Noncopyable
{
public:
    Tcp_v4_socket(void): m_fd(-1) {}
    explicit Tcp_v4_socket(int fd): m_fd(fd) {}
    ~Tcp_v4_socket(void);

public:
    void set_fd(int fd);
    int get_fd(void) const;

public:
    int init_sock(void);
    int close_sock(void);
    int bind_sock(Sock_addr_v4 &sa_v4) const;
    int listen_sock(int qs) const;
    int accept_sock(Sock_addr_v4 &sa_v4) const;
    int connect_sock(Sock_addr_v4 &sa_v4) const;
    int get_peer_addr(Sock_addr_v4 &sa_v4) const;
    int get_local_addr(Sock_addr_v4 &sa_v4) const;

    int set_reuse_addr(void) const;
    int set_nonblock(void) const;
    int set_keep_alive(void) const;
    int unset_linger(void) const;
    int unset_nagle(void) const;

public:
    int read_sock(char *buf, size_t len);
    int readn_sock(char *buf, size_t len);
    int write_sock(const char *buf, size_t len);
    int writen_sock(const char *buf, size_t len);

private:
    int m_fd;
};

} //namespace HVN

#endif


