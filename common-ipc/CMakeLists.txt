cmake_minimum_required(VERSION 2.8.4)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

# find host dir and set CMAKE_TOOLCHAIN_FILE before call project
execute_process(COMMAND which ${CMAKE_C_COMPILER} 
                OUTPUT_VARIABLE gcc_full_path)
get_filename_component(gcc_full_dir ${gcc_full_path} DIRECTORY)
set(HOST_DIR "${gcc_full_dir}/..")
set(CMAKE_TOOLCHAIN_FILE "${HOST_DIR}/share/buildroot/toolchainfile.cmake")

project(${CURRENT_FOLDER})
add_definitions(-Wall)

set(toolkit_root ${CMAKE_CURRENT_SOURCE_DIR}/../easyeai-api)

# -L
link_directories(${toolkit_root}/common_api/system_opt)
link_directories(${toolkit_root}/common_api/log_manager)
link_directories(${toolkit_root}/common_api/ipc)

# -I
set(api_inc
	${toolkit_root}/common_api/system_opt
	${toolkit_root}/common_api/log_manager
	${toolkit_root}/common_api/ipc
	)

#--------------------------
# test-IPC-opt_AClient
#--------------------------
add_executable(test-IPC-opt_AClient test-IPC-opt_AClient.c) #-o
target_link_libraries(test-IPC-opt_AClient ipc system_opt log_manager pthread ini stdc++) #-l
target_include_directories(test-IPC-opt_AClient PRIVATE ${api_inc}) #-I

#--------------------------
# test-IPC-opt_BClient
#--------------------------
add_executable(test-IPC-opt_BClient test-IPC-opt_BClient.c) #-o
target_link_libraries(test-IPC-opt_BClient ipc system_opt log_manager pthread ini stdc++) #-l
target_include_directories(test-IPC-opt_BClient PRIVATE ${api_inc}) #-I

#--------------------------
# test-IPC-opt_Server
#--------------------------
add_executable(test-IPC-opt_Server test-IPC-opt_Server.c) #-o
target_link_libraries(test-IPC-opt_Server ipc system_opt log_manager  pthread ini stdc++) #-l
target_include_directories(test-IPC-opt_Server PRIVATE ${api_inc}) #-I

