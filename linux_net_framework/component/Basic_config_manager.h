#ifndef __BASIC_CONFIG_MANAGER__
#define __BASIC_CONFIG_MANAGER__

#include <string>
#include "../../linux_program_libs/utils/Singleton.h"
#include "../../linux_program_libs/xml/Xml.h"

class Basic_config_manager: public HVN::Singleton<Basic_config_manager>
{
private:
    friend class HVN::Singleton<Basic_config_manager>;
    Basic_config_manager(void): m_localhost_ip("127.0.0.1"), m_persist_timeout(1), m_middle_server_port(63000), m_thread_pool_nr(4) {}
 
public:
    int initial(std::string xml_file);
    void show_config(void);

public:
    std::string get_localhost_ip(void)
    { return this->m_localhost_ip; }
    int get_persist_timeout(void)
    { return this->m_persist_timeout; }
    int get_middle_server_port(void)
    { return this->m_middle_server_port; }
    int get_thread_pool_nr(void)
    { return this->m_thread_pool_nr; }

private:
    int init_localhost_ip(void);
    int init_persist_timeout(void);
    int init_middle_server_port(void);
    int init_thread_pool_nr(void);

private:
    std::string m_localhost_ip;
    int m_persist_timeout;
    int m_middle_server_port;
    int m_thread_pool_nr;
    HVN::Xml m_xml;
};

#endif

