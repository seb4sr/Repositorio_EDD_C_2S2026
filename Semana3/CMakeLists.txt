cmake_minimum_required(VERSION 3.20)

project(Semana3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ListaCircularSimple
    ListaCircularSimple/main.cpp
    ListaCircularSimple/ListaCircularSimple.cpp
    ListaCircularSimple/ListaCircularSimple.h
)

add_executable(ListaCircularDoble
    ListaCircularDoble/main.cpp
    ListaCircularDoble/ListaCircularDoble.cpp
    ListaCircularDoble/ListaCircularDoble.h
)
