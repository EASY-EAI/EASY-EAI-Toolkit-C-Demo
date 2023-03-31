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
# test-disp-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/display)	#-L
link_directories(${toolkit_root}/peripheral_api/camera)		#-L
add_executable(test-disp-cam test-disp-cam.c)			#-o
target_link_libraries(test-disp-cam camera easymedia rkaiq rga display pthread)	#-l
target_include_directories(test-disp-cam PRIVATE ${api_inc})	#-I

#--------------------------
# test-disp-pro-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/display)	#-L
link_directories(${toolkit_root}/peripheral_api/camera)		#-L
add_executable(test-disp-pro-cam test-disp-pro-cam.c)		#-o
target_link_libraries(test-disp-pro-cam camera easymedia rkaiq rga display pthread)	#-l
target_include_directories(test-disp-pro-cam PRIVATE ${api_inc})	#-I
