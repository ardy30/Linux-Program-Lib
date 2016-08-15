#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
#include "Sock_addr_v4.h"
#include "../log/log.h"

int HVN::Sock_addr_v4::set_ip(std::string ip)
{
    if(inet_pton(AF_INET, ip.c_str(), &this->m_sin.sin_addr) <= 0)
    {
        LOGGING_ERROR(std::strerror(errno));
        return -1;
    }
    return 0;
}

int HVN::Sock_addr_v4::set_port(int port)
{
    if(port < 0 || port > 65535)
    {
        LOGGING_ERROR("Port is not a valid network port");
        return -1;
    }
    this->m_sin.sin_port = htons(port);
    return 0;
}

void HVN::Sock_addr_v4::set_by_sockaddr_in(const sockaddr_in &sin)
{
    this->m_sin = sin;
}

std::string HVN::Sock_addr_v4::get_ip(void) const
{
    char buf[64];
    std::string ip = "0.0.0.0";
    if(inet_ntop(AF_INET, &this->m_sin.sin_addr, buf, sizeof(buf)) == NULL)
    {
        LOGGING_ERROR(std::strerror(errno));
        return ip;
    }
    ip = buf;
    return ip;
}

int HVN::Sock_addr_v4::get_port(void) const
{
    return (int)ntohs(this->m_sin.sin_port);
}

sockaddr_in HVN::Sock_addr_v4::get_sockaddr_in(void) const
{
    return this->m_sin;
}
    
bool HVN::Sock_addr_v4::operator == (const Sock_addr_v4 &rhs) const
{
    if(this->get_ip() == rhs.get_ip() && this->get_port() == rhs.get_port())
        return true;
    return false;
}



