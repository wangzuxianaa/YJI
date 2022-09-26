cmake_minimum_required(VERSION 3.2)
PROJECT(YJI)
# include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# rosbuild_init()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")  

find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
)

add_library(${PROJECT_NAME} SHARED
src/System.cc
src/UDPServer.cc
src/StatusMonitor.cc
# src/ChassisSerialPort.cpp
)

target_link_libraries(${PROJECT_NAME}
nlohmann_json::nlohmann_json)

add_executable(main 
src/main.cc)

target_link_libraries(main ${PROJECT_NAME})