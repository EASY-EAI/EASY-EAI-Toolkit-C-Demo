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
	${toolkit_root}/peripheral_api/camera
	)

#--------------------------
# test-usb-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-usb-cam test-usb-cam.c)		#-o
target_link_libraries(test-usb-cam pthread rkfacial easymedia rga camera)	#-l
target_include_directories(test-usb-cam PRIVATE ${api_inc})	#-I

#--------------------------
# test-multi-usb-cam
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-multi-usb-cam test-multi-usb-cam.c)		#-o
target_link_libraries(test-multi-usb-cam pthread rkfacial easymedia rga camera)	#-l
target_include_directories(test-multi-usb-cam PRIVATE ${api_inc})	#-I

#--------------------------
# test-mipi-rgb
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-mipi-rgb test-mipi-rgb.c)		#-o
target_link_libraries(test-mipi-rgb pthread easymedia rga camera rkaiq)	#-l
target_include_directories(test-mipi-rgb PRIVATE ${api_inc})	#-I

#--------------------------
# test-mipi-ir
#--------------------------
link_directories(${toolkit_root}/peripheral_api/camera)	#-L
add_executable(test-mipi-ir test-mipi-ir.c)		#-o
target_link_libraries(test-mipi-ir pthread easymedia rga camera rkaiq)	#-l
target_include_directories(test-mipi-ir PRIVATE ${api_inc})	#-I
