#include <iostream>
#include "linux_program_libs/log/log.h"
#include "linux_program_libs/utils/Type_convertor.h"
#include "System_config_manager.h"

int System_config_manager::initial(std::string xml_file)
{
    if(!this->m_xml.load_from_file(xml_file.c_str()))
    {
        LOGGING_ERROR("load_from_file");
        return -1;
    }


    return 0;
}

void System_config_manager::show_config(void)
{
    std::cout << "============= system config ==============" << std::endl;

    std::cout << "==========================================" << std::endl;
}

