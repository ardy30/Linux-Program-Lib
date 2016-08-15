#include <iostream>
#include "../../linux_program_libs/log/log.h"
#include "../../linux_program_libs/utils/Type_convertor.h"
#include "Basic_config_manager.h"

int Basic_config_manager::initial(std::string xml_file)
{
    if(!this->m_xml.load_from_file(xml_file.c_str()))
    {
        LOGGING_ERROR("load_from_file");
        return -1;
    }

    if(this->init_localhost_ip())
        return -1;
    if(this->init_persist_timeout())
        return -1;
    if(this->init_middle_server_port())
        return -1;
    if(this->init_thread_pool_nr())
        return -1;

    return 0;
}

void Basic_config_manager::show_config(void)
{
    std::cout << "============= basic config ===============" << std::endl;
    std::cout << "local host ip: " << this->get_localhost_ip() << std::endl;
    std::cout << "persist timeout: " << this->get_persist_timeout() << std::endl;
    std::cout << "middle server port: " << this->get_middle_server_port() << std::endl;
    std::cout << "thread pool number: " << this->get_thread_pool_nr() << std::endl;
    std::cout << "==========================================" << std::endl;
}

int Basic_config_manager::init_localhost_ip(void)
{
    std::string tmp_str;
    if(this->m_xml.get_first_node_value_by_xpath("/CONFIG/BASIC_CONFIG/LOCALHOST_IP", tmp_str))
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/LOCALHOST_IP");
        return -1;
    }
    this->m_localhost_ip = tmp_str;
    return 0;
}

int Basic_config_manager::init_persist_timeout(void)
{
    std::string tmp_str;
    if(this->m_xml.get_first_node_value_by_xpath("/CONFIG/BASIC_CONFIG/PERSIST_TIMEOUT", tmp_str))
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/PERSIST_TIMEOUT");
        return -1;
    }

    this->m_persist_timeout = HVN::Type_convertor<std::string, int>::conv(tmp_str);
    if(this->m_persist_timeout < 0 || this->m_persist_timeout > 100)
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/PERSIST_TIMEOUT");
        return -1;
    }
    return 0;
}

int Basic_config_manager::init_middle_server_port(void)
{
    std::string tmp_str;
    if(this->m_xml.get_first_node_value_by_xpath("/CONFIG/BASIC_CONFIG/MIDDLE_SERVER_PORT", tmp_str))
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/MIDDLE_SERVER_PORT");
        return -1;
    }

    this->m_middle_server_port = HVN::Type_convertor<std::string, int>::conv(tmp_str);
    if(this->m_middle_server_port < 0 || this->m_middle_server_port > 65535)
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/MIDDLE_SERVER_PORT");
        return -1;
    }
    return 0;
}

int Basic_config_manager::init_thread_pool_nr(void)
{
    std::string tmp_str;
    if(this->m_xml.get_first_node_value_by_xpath("/CONFIG/BASIC_CONFIG/THREAD_POOL_NR", tmp_str))
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/THREAD_POOL_NR");
        return -1;
    }

    this->m_thread_pool_nr = HVN::Type_convertor<std::string, int>::conv(tmp_str);
    if(this->m_thread_pool_nr < 0 || this->m_thread_pool_nr > 10)
    {
        LOGGING_ERROR("/CONFIG/BASIC_CONFIG/THREAD_POOL_NR");
        return -1;
    }
    return 0;
}


