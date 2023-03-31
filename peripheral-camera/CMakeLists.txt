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
	${toolkit_root}/peripheral_api/camera
	)

#--------------------------
# test-usb-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-usb-cam test-usb-cam.c)		#-o
target_link_libraries(test-usb-cam camera easymedia rockchip_mpp rga pthread)	#-l
target_include_directories(test-usb-cam PRIVATE ${api_inc})	#-I

#--------------------------
# test-multi-usb-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-multi-usb-cam test-multi-usb-cam.c)		#-o
target_link_libraries(test-multi-usb-cam camera easymedia rockchip_mpp rga pthread)	#-l
target_include_directories(test-multi-usb-cam PRIVATE ${api_inc})	#-I

#--------------------------
# test-mipi-rgb
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-mipi-rgb test-mipi-rgb.c)		#-o
target_link_libraries(test-mipi-rgb camera easymedia rga rkaiq pthread)	#-l
target_include_directories(test-mipi-rgb PRIVATE ${api_inc})	#-I

#--------------------------
# test-mipi-ir
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-mipi-ir test-mipi-ir.c)		#-o
target_link_libraries(test-mipi-ir camera easymedia rga rkaiq pthread)	#-l
target_include_directories(test-mipi-ir PRIVATE ${api_inc})	#-I
