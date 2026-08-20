#include "MatrizDispersa.h"

#include <iostream>

int main() {
    MatrizDispersa matriz;

    matriz.insertarValor(0, 0, 5);
    matriz.insertarValor(0, 3, 8);
    matriz.insertarValor(1, 1, 2);
    matriz.insertarValor(2, 0, -3);
    matriz.insertarValor(2, 4, 7);
    matriz.insertarValor(3, 2, 1);
    matriz.insertarValor(4, 4, 9);
    matriz.insertarValor(5, 5, 4);

    std::cout << "--- Matriz recien cargada ---\n";
    matriz.mostrar();

    std::cout << "Valor en (2, 4): " << matriz.obtenerValor(2, 4) << "\n";
    std::cout << "Valor en (5, 5): " << matriz.obtenerValor(5, 5) << "\n";

    matriz.eliminarValor(0, 3);
    matriz.eliminarValor(2, 0);

    std::cout << "\n--- Matriz despues de eliminar (0, 3) y (2, 0) ---\n";
    matriz.mostrar();

    matriz.graficar();

    return 0;
}
