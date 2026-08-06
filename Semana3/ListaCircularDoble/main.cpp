#include "ListaCircularDoble.h"

#include <iostream>
#include <string>

int main() {
    ListaCircularDoble lista;
    int opcion;

    do {
        std::cout << "\n--- Lista Circular Doble de Amigos ---\n";
        std::cout << "1. Insertar amigo\n";
        std::cout << "2. Eliminar amigo\n";
        std::cout << "3. Graficar lista\n";
        std::cout << "4. Mostrar lista\n";
        std::cout << "5. Mostrar lista en reversa\n";
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nombre;
            int edad;
            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "Edad: ";
            std::cin >> edad;
            lista.insertar(nombre, edad);
            std::cout << "Amigo " << nombre << " agregado.\n";

        } else if (opcion == 2) {
            std::string nombre;
            std::cout << "Nombre del amigo a eliminar: ";
            std::cin >> nombre;
            std::cout << (lista.eliminar(nombre)
                              ? "Amigo eliminado.\n"
                              : "No se encontro amigo con ese nombre.\n");

        } else if (opcion == 3) {
            lista.graficar();

        } else if (opcion == 4) {
            lista.mostrar();

        } else if (opcion == 5) {
            lista.mostrarInverso();
        }
    } while (opcion != 0);

    return 0;
}
