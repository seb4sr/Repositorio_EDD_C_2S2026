#include "ArbolB4.h"

#include <iostream>

int main() {
    ArbolB4 arbol;

    arbol.insertar("Ana", 10);
    arbol.insertar("Luis", 20);
    arbol.insertar("Marta", 30);
    arbol.insertar("Carlos", 40);
    arbol.insertar("Sofia", 50);
    arbol.insertar("Diego", 60);
    arbol.insertar("Valentina", 70);
    arbol.insertar("Javier", 80);
    arbol.insertar("Camila", 90);
    arbol.insertar("Andres", 100);
    arbol.insertar("Paola", 110);
    arbol.insertar("Ricardo", 120);

    std::cout << "--- Arbol B de orden 4 recien cargado ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();

    std::cout << (arbol.buscar(90)
                      ? "Se encontro un amigo con 90 anios.\n"
                      : "No se encontro un amigo con 90 anios.\n");



    std::cout << "\n--- Arbol despues de eliminar las edades 10, 120 y 60 ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();

    arbol.graficar();

    return 0;
}
