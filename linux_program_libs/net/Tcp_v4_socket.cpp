/*
 * =====================================================================================
 *
 *       Filename:  Tcp_v4_socket.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/09/11 00:16:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Heaven (), zhanwenhan@163.com
 *        Company:  NDSL
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <cstring>
#include "Tcp_v4_socket.h"
#include "../log/log.h"

HVN::Tcp_v4_socket::~Tcp_v4_socket(void)
{
    if(this->m_fd != -1)
        LOGGING_WARN("Tcp_v4_socket destruct, but fd has not close");
}

void HVN::Tcp_v4_socket::set_fd(int fd)
{
    this->m_fd = fd;
}

int HVN::Tcp_v4_socket::get_fd(void) const
{
    return this->m_fd;
}

int HVN::Tcp_v4_socket::init_sock(void)
{
    this->close_sock();
    this->m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->m_fd == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::close_sock(void)
{
    if(this->m_fd == -1)
        return 0;
CLOSE_AGAIN:
    if(close(this->m_fd) == -1)
    {
        if(errno == EINTR)
            goto CLOSE_AGAIN;
        LOGGING_WARN(std::strerror(errno));
        this->m_fd = -1;
        return -1;
    }
    this->m_fd = -1;
    return 0;
}

int HVN::Tcp_v4_socket::bind_sock(Sock_addr_v4 &sa_v4) const
{
    struct sockaddr_in servaddr = sa_v4.get_sockaddr_in();
    if(bind(this->m_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::listen_sock(int qs) const
{
    if(listen(this->m_fd, qs) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::accept_sock(Sock_addr_v4 &sa_v4) const
{
    int fd = -1;
    struct sockaddr_in cliaddr;
    unsigned int len = sizeof(cliaddr);
    std::memset(&cliaddr, 0, len);
ACCEPT_AGAIN:
    if((fd = accept(this->m_fd, (struct sockaddr *)&cliaddr, &len)) == -1)
    {
        if(errno == EINTR)
            goto ACCEPT_AGAIN;
        LOGGING_WARN(std::strerror(errno));
        return fd;
    }
    sa_v4.set_by_sockaddr_in(cliaddr);
    return fd;
}

int HVN::Tcp_v4_socket::connect_sock(Sock_addr_v4 &sa_v4) const
{
    struct sockaddr_in servaddr = sa_v4.get_sockaddr_in();
    return connect(this->m_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

int HVN::Tcp_v4_socket::get_peer_addr(Sock_addr_v4 &sa_v4) const
{
    sockaddr_in peeraddr;
    std::memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t len = sizeof(peeraddr);
    if(getpeername(this->m_fd, (sockaddr *)&peeraddr, &len) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    sa_v4.set_by_sockaddr_in(peeraddr);
    return 0;
}

int HVN::Tcp_v4_socket::get_local_addr(Sock_addr_v4 &sa_v4) const
{
    sockaddr_in localaddr;
    std::memset(&localaddr, 0, sizeof(localaddr));
    socklen_t len = sizeof(localaddr);
    if(getsockname(this->m_fd, (sockaddr *)&localaddr, &len) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    sa_v4.set_by_sockaddr_in(localaddr);
    return 0;
}

int HVN::Tcp_v4_socket::set_reuse_addr(void) const
{
    int val = 1;
    if(setsockopt(this->m_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&val, sizeof(val)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::set_nonblock(void) const
{
    int val;
    if((val = fcntl(this->m_fd, F_GETFL, 0)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    val |= O_NONBLOCK;
    if(fcntl(this->m_fd, F_SETFL, val) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::set_keep_alive(void) const
{
    int val = 1;
    if(setsockopt(this->m_fd, SOL_SOCKET, SO_KEEPALIVE, (const void *)&val, sizeof(val)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::unset_linger(void) const
{
    struct linger ling = { 0, 0 };
    if(setsockopt(this->m_fd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::unset_nagle(void) const
{
    int val = 1;
    if(setsockopt(this->m_fd, IPPROTO_TCP, TCP_NODELAY, (const void*)&val, sizeof(val)) == -1)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Tcp_v4_socket::read_sock(char *buf, size_t len)
{
    int ret = 0;
READ_AGAIN:
    if((ret = read(this->m_fd, buf, len)) == -1)
        if(errno == EINTR)
            goto READ_AGAIN;
    return ret;
}

int HVN::Tcp_v4_socket::readn_sock(char *buf, size_t len)
{
    int nleft = 0, nread = 0;
    char *ptr = NULL;

    ptr = buf;
    nleft = len;
    while(nleft > 0)
    {
        if((nread = read(this->m_fd, ptr, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
            {
                LOGGING_ERROR(std::strerror(errno));
                return -1;
            }
        }
        else if(nread == 0)
            break;

        nleft -= nread;
        ptr += nread;
    }
    return len - nleft;
}

int HVN::Tcp_v4_socket::write_sock(const char *buf, size_t len)
{
    int ret = 0;
WRITE_AGAIN:
    if((ret = write(this->m_fd, buf, len)) == -1)
        if(errno == EINTR)
            goto WRITE_AGAIN;
    return ret;
}

int HVN::Tcp_v4_socket::writen_sock(const char *buf, size_t len)
{
    int nleft = 0, nwrite = 0;
    const char *ptr = NULL;

    ptr = buf;
    nleft = len;
    while(nleft > 0)
    {
        if((nwrite = write(this->m_fd, ptr, nleft)) <= 0)
        {
            if(nwrite < 0 && errno == EINTR)
                nwrite = 0;
            else
            {
                LOGGING_ERROR(std::strerror(errno));
                return -1;
            }
        }
        nleft -= nwrite;
        ptr += nwrite;
    }
    return len;
}



