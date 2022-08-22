cmake_minimum_required(VERSION 3.22)
project(01_number)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_number main.cpp TestBasicNumber.cpp testchar.cpp testbit.cpp)
