INCLUDE_DIRECTORIES(BEFORE /usr/include)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(hello ${SRC_LIST})
#add_library(hello STATIC ${SRC_LIST})
#add_library(hello SHARED ${SRC_LIST})

#LINK_DIRECTORIES(directory1 directory2)
#TARGET_LINK_LIBRARIES(hello lib.a lib.so)

#ADD_DEFINITIONS(-DDEBUG -DABC)

#ADD_DEPENDENCIES(target-name depend-target1 depend-target2)

INSTALL(TARGETS hello RUNTIME DESTINATION bin)



