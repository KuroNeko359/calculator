cmake_minimum_required(VERSION 4.0)
project(calculator C)

include_directories(include)

set(CMAKE_C_STANDARD 11)

add_executable(calculator main.c
        src/dynamic_stack.c
        include/dynamic_stack.h
        include/calculator.h
        src/calculator.c)
