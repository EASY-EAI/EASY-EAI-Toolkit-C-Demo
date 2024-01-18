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
	${CMAKE_SYSROOT}/usr/include/rkmedia
	${toolkit_root}/peripheral_api/camera
	${toolkit_root}/peripheral_api/display
	)

#--------------------------
# test-display
#--------------------------
link_directories(${toolkit_root}/peripheral_api/display)          #-L
add_executable(test-display test-display.c)                       #-o
target_link_libraries(test-display display easymedia rga pthread) #-l
target_include_directories(test-display PRIVATE ${api_inc})       #-I


#--------------------------
# test-display-pro
#--------------------------
link_directories(${toolkit_root}/peripheral_api/display)              #-L
add_executable(test-display-pro test-display-pro.c)                   #-o
target_link_libraries(test-display-pro display easymedia rga pthread) #-l
target_include_directories(test-display-pro PRIVATE ${api_inc})       #-I
