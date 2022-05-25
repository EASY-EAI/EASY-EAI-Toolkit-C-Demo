cmake_minimum_required(VERSION 2.8.4)

STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} )
MESSAGE("current project: " ${CURRENT_FOLDER})

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

# find host dir and set CMAKE_TOOLCHAIN_FILE before call project
execute_process(COMMAND which ${CMAKE_C_COMPILER} 
                OUTPUT_VARIABLE gcc_full_path)
get_filename_component(gcc_full_dir ${gcc_full_path} DIRECTORY)
set(HOST_DIR "${gcc_full_dir}/..")
set(CMAKE_TOOLCHAIN_FILE "${HOST_DIR}/share/buildroot/toolchainfile.cmake")

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