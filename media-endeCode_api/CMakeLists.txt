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

# -I
set(api_inc
	${CMAKE_SYSROOT}/usr/include/rkfacial
	${toolkit_root}/common_api/log_manager
	${toolkit_root}/media_api/endeCode_api
	)

#--------------------------
# test-videoDeCode_api.c
#--------------------------
link_directories(${toolkit_root}/common_api/system_opt)
link_directories(${toolkit_root}/common_api/log_manager)
link_directories(${toolkit_root}/media_api/endeCode_api) #-L

add_executable(test-videoDeCode_api test-videoDeCode_api.c) #-o
target_link_libraries(test-videoDeCode_api endeCode_api system_opt log_manager ini rockchip_mpp avcodec avutil swresample pthread stdc++ rt) #-l
target_include_directories(test-videoDeCode_api PRIVATE ${api_inc}) #-I

#--------------------------
# test-videoEnCode_api.c
#--------------------------
link_directories(${toolkit_root}/common_api/system_opt)
link_directories(${toolkit_root}/common_api/log_manager)
link_directories(${toolkit_root}/media_api/endeCode_api) #-L

add_executable(test-videoEnCode_api test-videoEnCode_api.c) #-o
target_link_libraries(test-videoEnCode_api endeCode_api system_opt log_manager ini rockchip_mpp avcodec avutil swresample pthread stdc++) #-l
target_include_directories(test-videoEnCode_api PRIVATE ${api_inc}) #-I

