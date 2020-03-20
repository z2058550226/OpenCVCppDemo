cmake_minimum_required(VERSION 3.15)
project(OpenCVCppDemo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCVCppDemo grabCutWithMask.cpp)

target_link_libraries(OpenCVCppDemo ${OpenCV_LIBS})