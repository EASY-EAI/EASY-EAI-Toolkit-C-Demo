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

# -I
set(api_inc
	${CMAKE_SYSROOT}/usr/include/rkfacial
	${toolkit_root}/common_api/system_opt
	)

#--------------------------
# test-timepara-opt
#--------------------------
link_directories(${toolkit_root}/common_api/system_opt) #-L
add_executable(test-timepara-opt test-timepara-opt.c) #-o
target_link_libraries(test-timepara-opt stdc++ pthread system_opt) #-l
target_include_directories(test-timepara-opt PRIVATE ${api_inc}) #-I

#--------------------------
# test-netpara-opt
#--------------------------
link_directories(${toolkit_root}/common_api/system_opt) #-L
add_executable(test-netpara-opt test-netpara-opt.c) #-o
target_link_libraries(test-netpara-opt stdc++ pthread system_opt) #-l
target_include_directories(test-netpara-opt PRIVATE ${api_inc}) #-I

#--------------------------
# test-thread-opt
#--------------------------
link_directories(${toolkit_root}/common_api/system_opt) #-L
add_executable(test-thread-opt test-thread-opt.c) #-o
target_link_libraries(test-thread-opt stdc++ pthread system_opt) #-l
target_include_directories(test-thread-opt PRIVATE ${api_inc}) #-I
