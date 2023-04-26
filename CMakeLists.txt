cmake_minimum_required(VERSION 3.25)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(simple_shell
        main.c
        main.h utilities.c functions.c)