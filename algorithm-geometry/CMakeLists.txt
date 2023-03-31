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
	${toolkit_root}/algorithm_api/geometry
	)

link_directories(${toolkit_root}/algorithm_api/geometry) #-L
#--------------------------
# test-point_n_rect
#--------------------------
add_executable(test-point_n_rect test-point_n_rect.c) #-o
target_link_libraries(test-point_n_rect geometry stdc++) #-l
target_include_directories(test-point_n_rect PRIVATE ${api_inc}) #-I

#--------------------------
# test-square
#--------------------------
add_executable(test-square test-square.c) #-o
target_link_libraries(test-square geometry stdc++) #-l
target_include_directories(test-square PRIVATE ${api_inc}) #-I


#--------------------------
# test-geometry
#--------------------------
add_executable(test-geometry test-geometry.c) #-o
target_link_libraries(test-geometry geometry stdc++) #-l
target_include_directories(test-geometry PRIVATE ${api_inc}) #-I