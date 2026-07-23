#include "ListaEnlazadaSimple.h"

#include <iostream>

int main() {
    ListaEnlazadaSimple lista;

    std::cout << "Estado inicial:\n";
    lista.imprimir();

    lista.insertar(10);
    lista.insertar(20);
    lista.insertar(30);
    lista.insertar(40);

    std::cout << "\nDespues de insertar 10, 20, 30 y 40:\n";
    lista.imprimir();
    std::cout << "Tamano: " << lista.obtenerTamano() << '\n';

    std::cout << "\nEliminar 20: "
              << (lista.eliminar(20) ? "eliminado" : "no encontrado") << '\n';
    lista.imprimir();

    std::cout << "Eliminar 10: "
              << (lista.eliminar(10) ? "eliminado" : "no encontrado") << '\n';
    lista.imprimir();

    std::cout << "Eliminar 99: "
              << (lista.eliminar(99) ? "eliminado" : "no encontrado") << '\n';
    lista.imprimir();

    std::cout << "Tamano final: " << lista.obtenerTamano() << '\n';

    return 0;
}
