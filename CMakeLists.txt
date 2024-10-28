cmake_minimum_required(VERSION 3.29)
project(msfunc C)

set(CMAKE_C_STANDARD 11)

add_library(msfunc STATIC library.c)
