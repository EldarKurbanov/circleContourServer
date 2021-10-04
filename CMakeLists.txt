cmake_minimum_required(VERSION 3.20)
project(circleContourServer)

set(CMAKE_CXX_STANDARD 23)

add_executable(circleContourServer main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(circleContourServer ${OpenCV_LIBS})
