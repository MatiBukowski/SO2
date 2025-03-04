cmake_minimum_required(VERSION 3.29)
project(SO2)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/Project_1/Headers)

add_executable(SO2_P1 Project_1/Sources/main.cpp
        Project_1/Sources/philoProblem.cpp)
add_executable(SO2_P2 Project_2/main2.cpp)
