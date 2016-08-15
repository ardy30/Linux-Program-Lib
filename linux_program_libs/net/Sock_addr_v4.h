#ifndef __HVN_SOCK_ADDR_V4_H__
#define __HVN_SOCK_ADDR_V4_H__

#include <netinet/in.h>
#include <string>
#include <cstring>
#include <iostream>

namespace HVN
{

class Sock_addr_v4
{
public:
    Sock_addr_v4(void) 
    {
        std::memset(&this->m_sin, 0, sizeof(this->m_sin)); 
        this->m_sin.sin_family = AF_INET;
        this->m_sin.sin_addr.s_addr = htonl(INADDR_ANY);
        this->m_sin.sin_port = htons(0);
    }

public:
    int set_ip(std::string ip);
    int set_port(int port);
    void set_by_sockaddr_in(const sockaddr_in &sin);

    std::string get_ip(void) const;
    int get_port(void) const;
    sockaddr_in get_sockaddr_in(void) const;
    
    bool operator == (const Sock_addr_v4 &sa) const;
   
private:
    sockaddr_in m_sin;
};

} //namespace HVN
 
inline std::ostream &operator<<(std::ostream &os, HVN::Sock_addr_v4 &sa)
{ 
    os << "( IP: " << sa.get_ip() << ", Port: " << sa.get_port() << " )"; 
    return os; 
}

#endif

