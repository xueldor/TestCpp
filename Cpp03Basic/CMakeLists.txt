# cmake_minimum_required(VERSION <specify CMake version here>)
project(TestCpp)


set(CMAKE_CXX_STANDARD 98)

add_executable(TestCpp main.cpp AllFiles.h testScope2.cpp testScope.cpp)