cmake_minimum_required(VERSION 2.8)
project(ECHO_EXAM)

message(STATUS "BINARY dir is" ${PROJECT_BINARY_DIR})
message(STATUS "SOURCE dir is" ${PROJECT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

link_directories(${PROJECT_BINARY_DIR}/lib) 

add_definitions(-g)

add_subdirectory(linux_program_libs)
add_subdirectory(linux_net_framework)
add_subdirectory(src)

#set(CMAKE_INSTALL_PREFIX /tmp/heaven)
#install(FILES COPYRIGHT README DESTINATION share/doc)
#install(DIRECTORY doc/ DESTINATION share/doc)
#install(PROGRAMS xx.sh DESTINATION bin)


