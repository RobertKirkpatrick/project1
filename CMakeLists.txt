cmake_minimum_required(VERSION 3.15)
project(project1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(project1
        dictionary.c
        dictionary.h
        main.c
        spell.c)
