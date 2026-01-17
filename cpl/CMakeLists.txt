cmake_minimum_required(VERSION 4.1)
project(cpl C)

set(CMAKE_C_STANDARD 11)

add_executable(cpl main.c
        circle.c
        guess.c
        trifx.c)
