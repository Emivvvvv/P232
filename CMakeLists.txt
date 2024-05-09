cmake_minimum_required(VERSION 3.28)
project(P232 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(P232
        main.c
        P_header.c
        P_header.h
        utils.c
        utils.h)
