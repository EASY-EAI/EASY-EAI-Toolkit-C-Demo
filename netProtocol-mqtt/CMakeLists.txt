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
	${CMAKE_SOURCE_DIR}/include
	)

#--------------------------
# test-mqtt
#--------------------------
# link_directories(${CMAKE_SOURCE_DIR}/libs) #-L
add_executable(test-mqtt_publish test-mqtt_publish.c) #-o
add_executable(test-mqtt_subscription test-mqtt_subscription.c) #-o

target_link_libraries(test-mqtt_publish mosquitto    crypto ssl pthread stdc++) #-l
target_link_libraries(test-mqtt_subscription mosquitto    crypto ssl pthread stdc++) #-l

target_include_directories(test-mqtt_publish PRIVATE ${api_inc}) #-I
target_include_directories(test-mqtt_subscription PRIVATE ${api_inc}) #-I

