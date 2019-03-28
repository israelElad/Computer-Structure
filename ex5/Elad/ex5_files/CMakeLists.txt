cmake_minimum_required(VERSION 3.13)
project(ex5_files C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex5_files
        myfunction.c
        readBMP.c
        readBMP.h
        showBMP.c
        writeBMP.c
        writeBMP.h)
