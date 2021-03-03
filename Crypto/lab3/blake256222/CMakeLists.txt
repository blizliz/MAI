cmake_minimum_required(VERSION 3.13)
project(blake256 C)

set(CMAKE_C_STANDARD 11)

add_executable(blake256 main.c blake256.h)