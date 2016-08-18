include_directories(BEFORE /usr/include/libxml2)
#aux_source_directory(. SRC_LIST)

set(SRC_LIST 
    ./signal/Signal_manager.cpp
    ./log/Handle_log.cpp
    ./log/Console_logger.cpp
    ./net/Sock_addr_v4.cpp
    ./net/Tcp_v4_socket.cpp
    ./xml/Xml.cpp
    ./pthread/Thread.cpp
    ./utils/Time.cpp
    )

#add_executable(hello ${SRC_LIST})
add_library(linux_program_libs STATIC ${SRC_LIST})
#add_library(hello SHARED ${SRC_LIST})

#link_directories(directory1 directory2)
#target_link_libraries(linux_program_libs libxml2)

#add_definitions(-DDEBUG -DABC)

#add_dependencies(target-name depend-target1 depend-target2)

install(TARGETS linux_program_libs ARCHIVE DESTINATION lib)



