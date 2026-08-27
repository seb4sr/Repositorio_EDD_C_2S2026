cmake_minimum_required(VERSION 3.20)

project(Semana6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ArbolAVL
    ArbolAVL/main.cpp
    ArbolAVL/ArbolAVL.cpp
    ArbolAVL/ArbolAVL.h
)
