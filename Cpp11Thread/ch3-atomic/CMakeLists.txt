cmake_minimum_required(VERSION 3.16)
project(test_atomic)

set(CMAKE_CXX_STANDARD 14)
add_executable(test_atomic test_atomic.cpp)
target_link_libraries(test_atomic pthread)

add_executable(test_atomic_basic test_atomic_basic.cpp)
target_link_libraries(test_atomic_basic pthread)

