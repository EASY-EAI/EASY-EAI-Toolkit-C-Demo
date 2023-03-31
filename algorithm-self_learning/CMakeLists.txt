cmake_minimum_required(VERSION 2.8.4)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)


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
	${toolkit_root}/algorithm_api/self_learning
	)
# -L
link_directories(${toolkit_root}/algorithm_api/self_learning)

#--------------------------
# test-face-recognition
#--------------------------
find_package(OpenCV REQUIRED) 
add_executable(test-self-learning test-self_learning.cpp)		#-o
target_include_directories(test-self-learning PRIVATE ${api_inc} ${OpenCV_INCLUDE_DIRS})	#-I
target_link_libraries(test-self-learning pthread  self_learning rknn_api  ${OpenCV_LIBS} )

