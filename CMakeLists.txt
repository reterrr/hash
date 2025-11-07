cmake_minimum_required(VERSION 3.30)
project(sha256 C)

set(CMAKE_C_STANDARD 11)

add_library(sha256 STATIC library.c
        md4.h
        md4.c
        test.c)
