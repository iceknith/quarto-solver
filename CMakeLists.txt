cmake_minimum_required(VERSION 3.27)
project(quatro_solver_C__)

set(CMAKE_CXX_STANDARD 17)

#Flags for the profiler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(quatro_solver_C__ main.cpp)
