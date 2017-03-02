cmake_minimum_required(VERSION 3.6)
project(Life)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c pngOperator.c pngOperator.h gameOperator.c gameOperator.h gameSettings.c gameSettings.h)
add_executable(Life ${SOURCE_FILES})