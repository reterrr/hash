cmake_minimum_required(VERSION 3.30)
project(sha256 C)

set(CMAKE_C_STANDARD 11)

add_library(lib STATIC library.c
        md4.h
        md4.c
        md5.c
        md5.h
        myendian.h)

add_executable(sha256 test.c)
target_link_libraries(sha256 PRIVATE lib)
