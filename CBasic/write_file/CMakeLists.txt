cmake_minimum_required(VERSION 3.17)
project(write_file C)

set(CMAKE_C_STANDARD 99)

add_executable(write_file main.c only_readfile.c only_writefile.c read_writefile.c)