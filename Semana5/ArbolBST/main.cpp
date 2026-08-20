#include "ArbolBST.h"

#include <iostream>

int main() {
    ArbolBST arbol;

    arbol.insertar("Ana", 20);
    arbol.insertar("Luis", 22);
    arbol.insertar("Marta", 19);
    arbol.insertar("Carlos", 25);
    arbol.insertar("Sofia", 21);
    arbol.insertar("Diego", 17);
    arbol.insertar("Valentina", 24);
    arbol.insertar("Javier", 8);

    std::cout << "--- Arbol recien cargado ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();
    arbol.mostrarPreOrden();
    arbol.mostrarPostOrden();

    std::cout << (arbol.buscar(25)
                      ? "Se encontro un amigo con 25 anios.\n"
                      : "No se encontro un amigo con 25 anios.\n");

    arbol.eliminar(20);
    arbol.eliminar(17);

    std::cout << "\n--- Arbol despues de eliminar las edades 20 y 17 ---\n";
    std::cout << "Cantidad de amigos: " << arbol.obtenerCantidad() << "\n";
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << "\n";
    arbol.mostrarEnOrden();

    arbol.graficar();

    return 0;
}
