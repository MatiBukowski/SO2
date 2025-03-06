cmake_minimum_required(VERSION 3.28.1)
project(SO2)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/Project_1/Headers)
include_directories(${PROJECT_SOURCE_DIR}/Project_2/Headers)

add_executable(SO2_P1 Project_1/Sources/main.cpp
        Project_1/Sources/philoProblem.cpp
        Project_1/Sources/philoProblem2.cpp)
add_executable(SO2_P2 Project_2/Sources/main2.cpp
        Project_2/Sources/connection.cpp
        Project_2/Sources/server.cpp
        Project_2/Headers/server.h
        Project_2/Sources/client.cpp
        Project_2/Headers/client.h)

target_link_libraries(SO2_P2 PRIVATE Ws2_32)                # linking library Ws2_32 to use socket's function in Windows API

