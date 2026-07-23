cmake_minimum_required(VERSION 3.20)

project(Repositorio_EDD_C_2S2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Repositorio_EDD_C_2S2026
    src/main.cpp
)

add_executable(SintaxisBasica
    Semana1/Sintaxis/main.cpp
)

add_executable(ListaEnlazadaSimple
    Semana1/ListaEnlazadaSimple/main.cpp
    Semana1/ListaEnlazadaSimple/ListaEnlazadaSimple.cpp
    Semana1/ListaEnlazadaSimple/ListaEnlazadaSimple.h
)
