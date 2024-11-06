cmake_minimum_required(VERSION 3.29)
project(headers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(headers
    ALU.cpp
    ALU.h
    CPU.cpp
    CPU.h
    CU.cpp
    CU.h
    Machine.cpp
    Machine.h
    main.cpp
    Memory.cpp
    Memory.h
    Register.cpp
    Register.h)
