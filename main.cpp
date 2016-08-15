#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include "linux_program_libs/log/log.h"
#include "linux_net_framework/component/Basic_config_manager.h"
#include "System_config_manager.h"
#include "Main_body.h"

void sigfunc(int signo)
{
    std::exit(-1);
}

int main(int argc, char **argv)
{
    signal(SIGINT, sigfunc);
    int opt = 0;
    std::string config_file("./config.xml");
    while ((opt = getopt(argc, argv, "f:")) != -1) 
    {
        switch(opt)
        {
        case 'f':
            config_file = optarg;
            break;
        default:
            LOGGING_FATAL("usage: bin -f config_file");
            std::exit(-1);
            break;
        }
    }

    if(Basic_config_manager::get_pinstance()->initial(config_file))
    {
        LOGGING_FATAL("load basic config failed");
        std::exit(-1);
    }
    if(System_config_manager::get_pinstance()->initial(config_file))
    {
        LOGGING_FATAL("load system config failed");
        std::exit(-1);
    }
 
    Basic_config_manager::get_pinstance()->show_config();
    System_config_manager::get_pinstance()->show_config();

    Main_body::get_pinstance()->initial();

    while(1)
        sleep(90000000);
    return 0;
}

