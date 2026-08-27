#include "ArbolAVL.h"

#include <iostream>

int main() {
    ArbolAVL arbol;

    arbol.insertar("Ana", 10);
    arbol.insertar("Luis", 20);
    arbol.insertar("Marta", 30);
    arbol.insertar("Carlos", 40);
    arbol.insertar("Sofia", 50);
    arbol.insertar("Diego", 60);
    arbol.insertar("Valentina", 70);

    std::cout << "--- Arbol recien cargado (edades insertadas en orden ascendente) ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();
    arbol.mostrarPreOrden();
    arbol.mostrarPostOrden();

    std::cout << (arbol.buscar(50)
                      ? "Se encontro un amigo con 50 anios.\n"
                      : "No se encontro un amigo con 50 anios.\n");

    arbol.eliminar(70);
    arbol.eliminar(10);

    std::cout << "\n--- Arbol despues de eliminar las edades 70 y 10 ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();

    arbol.graficar();

    return 0;
}
