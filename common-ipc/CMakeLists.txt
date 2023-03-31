 cmake_minimum_required(VERSION 2.8.4)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)

cmake_host_system_information(RESULT arch_value QUERY OS_PLATFORM)

if(NOT "${arch_value}" STREQUAL "armv7l")
   include ($ENV{HOME}/configs/cross.cmake)
endif()

project(${CURRENT_FOLDER})
add_definitions(-Wall)

set(toolkit_root ${CMAKE_CURRENT_SOURCE_DIR}/../easyeai-api)

# -L
link_directories(${toolkit_root}/common_api/system_opt)
link_directories(${toolkit_root}/common_api/log_manager)
link_directories(${toolkit_root}/common_api/ipc)

# -I
set(api_inc
	${CMAKE_SYSROOT}/usr/include/rkfacial
	${toolkit_root}/common_api/system_opt
	${toolkit_root}/common_api/log_manager
	${toolkit_root}/common_api/ipc
	)

#--------------------------
# test-IPC-opt_Client
#--------------------------
add_executable(test-IPC-opt_Client test-IPC-opt_Client.c) #-o
target_link_libraries(test-IPC-opt_Client ipc system_opt log_manager pthread ini stdc++) #-l
target_include_directories(test-IPC-opt_Client PRIVATE ${api_inc}) #-I

#--------------------------
# test-IPC-opt_Server
#--------------------------
add_executable(test-IPC-opt_Server test-IPC-opt_Server.c) #-o
target_link_libraries(test-IPC-opt_Server ipc system_opt log_manager  pthread ini stdc++) #-l
target_include_directories(test-IPC-opt_Server PRIVATE ${api_inc}) #-I

