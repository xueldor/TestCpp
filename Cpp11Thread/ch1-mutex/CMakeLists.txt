cmake_minimum_required(VERSION 3.16)
project(test_mutex)

set(CMAKE_CXX_STANDARD 14)
add_executable(test_mutex test_mutex.cpp)
target_link_libraries(test_mutex pthread)

add_executable(test_unique_lock test_unique_lock.cpp)
target_link_libraries(test_unique_lock pthread)