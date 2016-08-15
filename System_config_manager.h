#ifndef __SYSTEM_CONFIG_MANAGER__
#define __SYSTEM_CONFIG_MANAGER__

#include <string>
#include "linux_program_libs/utils/Singleton.h"
#include "linux_program_libs/xml/Xml.h"

class System_config_manager: public HVN::Singleton<System_config_manager>
{
private:
    friend class HVN::Singleton<System_config_manager>;
    System_config_manager(void) {}
 
public:
    int initial(std::string xml_file);
    void show_config(void);

private:
    HVN::Xml m_xml;
};

#endif

