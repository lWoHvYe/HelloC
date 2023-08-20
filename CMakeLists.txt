cmake_minimum_required(VERSION 3.24)
project(HelloC C)

set(CMAKE_C_STANDARD 17)

add_executable(HelloC main.c loan.c loan.h
        concurrent.c
        concurrent.h)

target_link_libraries(HelloC m)