cmake_minimum_required(VERSION 3.20)

project(Semana4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ListaDeListas
    ListaDeListas/main.cpp
    ListaDeListas/ListaDeListas.cpp
    ListaDeListas/ListaDeListas.h
)