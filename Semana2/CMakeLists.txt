# Solicita CMake 3.20 o una version mas reciente para procesar este archivo.
cmake_minimum_required(VERSION 3.20)

# Crea el proyecto de las guias e indica que su lenguaje es C++ (CXX).
project(GuiasSemana2 LANGUAGES CXX)

# Solicita que todos los programas de esta guia se compilen con C++20.
set(CMAKE_CXX_STANDARD 20)
# Hace obligatorio C++20; CMake no puede reemplazarlo por una version anterior.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Evita depender de extensiones particulares de un compilador.
set(CMAKE_CXX_EXTENSIONS OFF)

# Las clases que usan Q_OBJECT (senales/slots) necesitan que Qt genere codigo
# adicional con el moc (Meta-Object Compiler). AUTOMOC hace que CMake lo
# ejecute automaticamente sobre cada header que declare Q_OBJECT.
set(CMAKE_AUTOMOC ON)

# Busca una instalacion de Qt6 y, si no la encuentra, intenta con Qt5; ambas
# lineas son necesarias porque el nombre del paquete cambia segun la version.
# Si CMake no la encuentra sola, indica la ruta con -DCMAKE_PREFIX_PATH
# al configurar (ver README.md de esta carpeta).
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Crea el ejecutable ContadorQtGuia a partir de los archivos del ejemplo.
add_executable(ContadorQtGuia
    # Punto de entrada: crea QApplication y la ventana principal.
    ContadorQt/main.cpp
    # Declaracion de la ventana (widgets, senales y slots).
    ContadorQt/ContadorWindow.h
    # Implementacion: construccion de la interfaz y logica del contador.
    ContadorQt/ContadorWindow.cpp
)

# Enlaza el ejecutable con el modulo Widgets de la version de Qt encontrada
# (Qt6::Widgets o Qt5::Widgets, segun corresponda).
target_link_libraries(ContadorQtGuia PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)