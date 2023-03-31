cmake_minimum_required(VERSION 2.8.4)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)

cmake_host_system_information(RESULT arch_value QUERY OS_PLATFORM)
message(STATUS "architecture: " ${arch_value})

if(NOT "${arch_value}" STREQUAL "armv7l")
	include ($ENV{HOME}/configs/cross.cmake)
endif()

project(${CURRENT_FOLDER})
add_definitions(-Wall)

set(toolkit_root ${CMAKE_CURRENT_SOURCE_DIR}/../easyeai-api)

find_package(OpenCV REQUIRED)
# -I
set(api_inc
	${toolkit_root}/common_api/font_engine
	${OpenCV_INCLUDE_DIRS}
	)
# -L
link_directories(${toolkit_root}/common_api/font_engine)

#--------------------------
# test-font_engine freetype bz2 stdc++
#--------------------------
add_executable(test-font_engine test-font_engine.cpp) #-o
target_include_directories(test-font_engine PRIVATE ${api_inc}) #-I
target_link_libraries(test-font_engine font_engine freetype
    -lopencv_calib3d 
    -lopencv_core 
    -lopencv_dnn 
    -lopencv_features2d 
    -lopencv_flann 
    -lopencv_highgui 
    -lopencv_imgcodecs 
    -lopencv_imgproc 
    -lopencv_ml 
    -lopencv_objdetect 
    -lopencv_photo 
    -lopencv_shape 
    -lopencv_stitching 
    -lopencv_superres 
    -lopencv_videoio 
    -lopencv_video 
    -lopencv_videostab)	#-l


