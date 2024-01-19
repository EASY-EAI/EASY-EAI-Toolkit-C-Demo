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
	set(CMAKE_CROSSCOMPILING TRUE)
	set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
	set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

	# find host dir and set CMAKE_TOOLCHAIN_FILE before call project
	execute_process(COMMAND which ${CMAKE_C_COMPILER} OUTPUT_VARIABLE gcc_full_path)
	get_filename_component(gcc_full_dir ${gcc_full_path} DIRECTORY)
	set(HOST_DIR "${gcc_full_dir}/..")
	set(CMAKE_TOOLCHAIN_FILE "${HOST_DIR}/share/buildroot/toolchainfile.cmake")
endif()

project(${CURRENT_FOLDER})
add_definitions(-Wall)

set(toolkit_root ${CMAKE_CURRENT_SOURCE_DIR}/../easyeai-api)

# -I
set(api_inc
	${toolkit_root}/peripheral_api/audio
)


set(aiTag test-ai)
link_directories(${toolkit_root}/peripheral_api/audio)  #-L
add_executable(${aiTag} test-ai.c)                      #-o
target_link_libraries(${aiTag} audio asound)            #-l
target_include_directories(${aiTag} PRIVATE ${api_inc})	#-I

set(aoTag test-ao)
link_directories(${toolkit_root}/peripheral_api/audio)  #-L
add_executable(${aoTag} test-ao.c)                      #-o
target_link_libraries(${aoTag} audio asound)            #-l
target_include_directories(${aoTag} PRIVATE ${api_inc})	#-I


