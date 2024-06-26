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
	${toolkit_root}/common_api/qrencode
	)

#--------------------------
# test-QRCode
#--------------------------
find_package(OpenCV REQUIRED) 
link_directories(${toolkit_root}/common_api/qrencode) #-L
add_executable(test-QRCode test-QRCode.c) #-o
target_link_libraries(test-QRCode qrencode stdc++ pthread  opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs ) #-l
target_include_directories(test-QRCode PRIVATE ${api_inc} ${OpenCV_INCLUDE_DIRS}) #-I


