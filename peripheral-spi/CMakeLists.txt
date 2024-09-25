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
	${toolkit_root}/peripheral_api/spi
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	)

#--------------------------
# test-rfid
#--------------------------
link_directories(${toolkit_root}/peripheral_api/spi) #-L
add_executable(test-rfid rfid.c dev/rc522.c)  #-o
target_link_libraries(test-rfid spi stdc++) #-l
target_include_directories(test-rfid PRIVATE ${api_inc}) #-I


#--------------------------
# test-fram
#--------------------------
link_directories(${toolkit_root}/peripheral_api/spi) #-L
add_executable(test-fram fram.c dev/mb85rs64.c)  #-o
target_link_libraries(test-fram spi stdc++) #-l
target_include_directories(test-fram PRIVATE ${api_inc}) #-I


#--------------------------
# test-spidev
#--------------------------
link_directories(${toolkit_root}/peripheral_api/spi) #-L
add_executable(test-spidev spidev_test.c)  #-o
target_link_libraries(test-spidev spi stdc++) #-l
target_include_directories(test-spidev PRIVATE ${api_inc}) #-I
