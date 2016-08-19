include_directories(BEFORE /usr/include/libxml2)
aux_source_directory(. SRC_LIST)

add_executable(echo_exam ${SRC_LIST})
#add_library(linux_program_libs STATIC ${SRC_LIST})
#add_library(hello SHARED ${SRC_LIST})

link_directories(${PROJECT_BINARY_DIR}/lib)

target_link_libraries(echo_exam 
    linux_program_libs 
    linux_net_framework
    librt.so 
    libpthread.so 
    libxml2.so 
    libevent.so 
    )

#add_definitions(-DDEBUG -DABC)

#add_dependencies(target-name depend-target1 depend-target2)

install(TARGETS echo_exam RUNTIME DESTINATION bin)



