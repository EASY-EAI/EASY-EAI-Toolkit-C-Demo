cmake_minimum_required(VERSION 3.10.2)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)

cmake_host_system_information(RESULT arch_value QUERY OS_PLATFORM)
message(STATUS "architecture: " ${arch_value})

if("${arch_value}" STREQUAL "armv7l")
	set(CMAKE_C_COMPILER "gcc")
	set(CMAKE_CXX_COMPILER "g++")
else()
	include ($ENV{HOME}/configs/cross.cmake)
endif()

	

project(${CURRENT_FOLDER})

add_definitions(-Wall)

set(toolkit_root ${CMAKE_CURRENT_SOURCE_DIR}/../easyeai-api)

#--------------------------
# test-iic
#--------------------------

# -I
set(api_inc
   ${CMAKE_SYSROOT}/usr/include/rkfacial
   ${toolkit_root}/peripheral_api/iic
   include/
)

set(ads1115 test-ads1115)
link_directories(${toolkit_root}/peripheral_api/iic) #-L
add_executable(${ads1115} test-ads1115.c) #-o
target_link_libraries(${ads1115} iic stdc++) #-l
target_include_directories(${ads1115} PRIVATE ${api_inc}) #-I



