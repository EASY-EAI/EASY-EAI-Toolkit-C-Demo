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
set(tcpclient test-tcpclient)
link_directories(${toolkit_root}/peripheral_api/tcpsocket)	#-L
add_executable(${tcpclient} test-tcpclient.c)		#-o
target_link_libraries(${tcpclient} pthread)	#-l
target_include_directories(${tcpclient} PRIVATE ${api_inc})	#-I

#--------------------------
# server
#--------------------------
set(tcpserver test-tcpserver)
link_directories(${toolkit_root}/peripheral_api/tcpsocket)	#-L
add_executable(${tcpserver} test-tcpserver.c)		#-o
target_link_libraries(${tcpserver} pthread)	#-l
target_include_directories(${tcpserver} PRIVATE ${api_inc})	#-I
