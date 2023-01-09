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
	${toolkit_root}/media_api/endeCode_api
	)

#--------------------------
# test-videoDeCode_api.c
#--------------------------
link_directories(${toolkit_root}/media_api/endeCode_api) #-L
add_executable(test-videoDeCode_api test-videoDeCode_api.c) #-o
target_link_libraries(test-videoDeCode_api endeCode_api rockchip_mpp pthread stdc++ rt) #-l
target_include_directories(test-videoDeCode_api PRIVATE ${api_inc}) #-I

#--------------------------
# test-videoEnCode_api.c
#--------------------------
link_directories(${toolkit_root}/media_api/endeCode_api) #-L
add_executable(test-videoEnCode_api test-videoEnCode_api.c) #-o
target_link_libraries(test-videoEnCode_api endeCode_api rockchip_mpp pthread stdc++) #-l
target_include_directories(test-videoEnCode_api PRIVATE ${api_inc}) #-I

