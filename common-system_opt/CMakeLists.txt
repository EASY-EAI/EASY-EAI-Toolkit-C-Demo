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

# -L
link_directories(${toolkit_root}/common_api/system_opt)

# -I
set(api_inc
	${CMAKE_SYSROOT}/usr/include/rkfacial
	${toolkit_root}/common_api/system_opt
	)

#--------------------------
# test-timepara-opt
#--------------------------
add_executable(test-timepara-opt test-timepara-opt.c) #-o
target_link_libraries(test-timepara-opt  system_opt pthread ini stdc++) #-l
target_include_directories(test-timepara-opt PRIVATE ${api_inc}) #-I

#--------------------------
# test-thread-opt
#--------------------------
add_executable(test-thread-opt test-thread-opt.c) #-o
target_link_libraries(test-thread-opt system_opt pthread ini stdc++) #-l
target_include_directories(test-thread-opt PRIVATE ${api_inc}) #-I


