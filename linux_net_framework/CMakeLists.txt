include_directories(BEFORE /usr/include/libxml2)
#aux_source_directory(. SRC_LIST)

set(SRC_LIST 
    ./common/Timer.cpp
    ./common/Scheduler.cpp
    ./common/Task.cpp
    ./common/Sock_nh.cpp
    ./common/Sock.cpp
    ./common/Listener.cpp
    ./common/Task_factory.cpp
    ./component/Middle_server_task.cpp
    ./component/Persist_timer_task.cpp
    ./component/Thread_pool.cpp
    ./component/Basic_config_manager.cpp
    )

#add_executable(hello ${SRC_LIST})
add_library(linux_net_framework STATIC ${SRC_LIST})
#add_library(hello SHARED ${SRC_LIST})

#link_directories(directory1 directory2)
#target_link_libraries(linux_net_framework libxml2)

#add_definitions(-DDEBUG -DABC)

#add_dependencies(target-name depend-target1 depend-target2)

install(TARGETS linux_net_framework ARCHIVE DESTINATION lib)



