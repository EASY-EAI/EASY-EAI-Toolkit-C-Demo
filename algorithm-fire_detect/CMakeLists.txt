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
	${toolkit_root}/algorithm_api/fire_detect
	)
# -L
link_directories(${toolkit_root}/algorithm_api/fire_detect)

#--------------------------
# test-person-detect
#--------------------------
add_executable(test-fire-detect test-fire-detect.cpp)		#-o
target_include_directories(test-fire-detect PRIVATE ${api_inc})	#-I
target_link_libraries(test-fire-detect pthread fire_detect rknn_api
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

