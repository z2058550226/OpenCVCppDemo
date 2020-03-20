cmake_minimum_required(VERSION 3.15)
project(TestCmake)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCVCppDemo grabCutWithMask.cpp)

target_link_libraries(TestCmake ${OpenCV_LIBS})