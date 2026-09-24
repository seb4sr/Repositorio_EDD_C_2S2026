cmake_minimum_required(VERSION 3.20)

project(Semana10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Servidor
    main.cpp
)

target_include_directories(Servidor PRIVATE lib)

if(WIN32)
    target_link_libraries(Servidor PRIVATE ws2_32)
endif()
