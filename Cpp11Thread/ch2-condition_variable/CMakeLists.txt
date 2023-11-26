cmake_minimum_required(VERSION 3.16)
project(test_condition)

set(CMAKE_CXX_STANDARD 14)
add_executable(test_condition test_conditionvariable.cpp)
target_link_libraries(test_condition pthread)

