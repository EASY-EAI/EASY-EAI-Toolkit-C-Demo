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

# -I
set(api_inc
	${toolkit_root}/peripheral_api/tcpsocket
	)

#--------------------------
# client
#--------------------------
set(udpclient test-udpclient)
link_directories(${toolkit_root}/peripheral_api/tcpsocket)	#-L
add_executable(${udpclient} test-udpclient.c)		#-o
target_link_libraries(${udpclient} pthread)	#-l
target_include_directories(${udpclient} PRIVATE ${api_inc})	#-I

#--------------------------
# server
#--------------------------
set(udpserver test-udpserver)
link_directories(${toolkit_root}/peripheral_api/tcpsocket)	#-L
add_executable(${udpserver} test-udpserver.c)		#-o
target_link_libraries(${udpserver} pthread)	#-l
target_include_directories(${udpserver} PRIVATE ${api_inc})	#-I
