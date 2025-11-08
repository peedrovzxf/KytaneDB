cmake_minimum_required(VERSION 4.0)
project(kytane-db C)

set(CMAKE_C_STANDARD 17)

include_directories(include)

add_executable(kytane-db
        src/main.c
        include/server.h
        src/server.c
        include/handler.h
        src/handler.c
        include/storage.h
        src/storage.c)
