cmake_minimum_required(VERSION 3.20)

project(Semana5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MatrizDispersa
    MatrizDispersa/main.cpp
    MatrizDispersa/MatrizDispersa.cpp
    MatrizDispersa/MatrizDispersa.h
)

add_executable(ArbolBST
    ArbolBST/main.cpp
    ArbolBST/ArbolBST.cpp
    ArbolBST/ArbolBST.h
)
