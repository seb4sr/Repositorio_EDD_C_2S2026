
#include "ListaDeListas.h"

#include <iostream>
#include <string>

int main() {
    ListaDeListas lista;

    lista.insertarGrupo("g1");
    lista.insertarIntegrante("g1", "Ana", 20);
    lista.insertarIntegrante("g1", "Luis", 22);
    lista.insertarIntegrante("g1", "Marta", 19);
    lista.insertarIntegrante("g1", "Carlos", 25);

    lista.insertarGrupo("g2");
    lista.insertarIntegrante("g2", "Sofia", 21);
    lista.insertarIntegrante("g2", "Diego", 23);
    lista.insertarIntegrante("g2", "Valentina", 20);
    lista.insertarIntegrante("g2", "Andres", 24);
    lista.insertarIntegrante("g2", "Camila", 22);
    lista.insertarIntegrante("g2", "Javier", 26);
    lista.insertarIntegrante("g2", "Paola", 19);

    lista.insertarGrupo("g4");
    lista.insertarIntegrante("g4", "Ricardo", 27);
    lista.insertarIntegrante("g4", "Daniela", 20);
    lista.insertarIntegrante("g4", "Fernando", 23);
    lista.insertarIntegrante("g4", "Gabriela", 21);
    lista.insertarIntegrante("g4", "Hector", 25);
    lista.insertarIntegrante("g4", "Isabel", 19);
    lista.insertarIntegrante("g4", "Jorge", 24);
    lista.insertarIntegrante("g4", "Karla", 22);

    int opcion;

    do {
        std::cout << "\n--- Lista de Listas de Grupos ---\n";
        std::cout << "1. Insertar grupo\n";
        std::cout << "2. Insertar integrante en un grupo\n";
        std::cout << "3. Eliminar grupo\n";
        std::cout << "4. Eliminar integrante de un grupo\n";
        std::cout << "5. Mostrar todo\n";
        std::cout << "6. Graficar\n";
        std::cout << "0. Salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nombreGrupo;
            std::cout << "Nombre del grupo: ";
            std::cin >> nombreGrupo;
            std::cout << (lista.insertarGrupo(nombreGrupo)
                              ? "Grupo agregado.\n"
                              : "Ya existe un grupo con ese nombre.\n");

        } else if (opcion == 2) {
            std::string nombreGrupo;
            std::string nombre;
            int edad;
            std::cout << "Nombre del grupo: ";
            std::cin >> nombreGrupo;
            std::cout << "Nombre del integrante: ";
            std::cin >> nombre;
            std::cout << "Edad: ";
            std::cin >> edad;
            std::cout << (lista.insertarIntegrante(nombreGrupo, nombre, edad)
                              ? "Integrante agregado.\n"
                              : "No existe un grupo con ese nombre.\n");

        } else if (opcion == 3) {
            std::string nombreGrupo;
            std::cout << "Nombre del grupo a eliminar: ";
            std::cin >> nombreGrupo;
            std::cout << (lista.eliminarGrupo(nombreGrupo)
                              ? "Grupo eliminado.\n"
                              : "No se encontro un grupo con ese nombre.\n");

        } else if (opcion == 4) {
            std::string nombreGrupo;
            std::string nombre;
            std::cout << "Nombre del grupo: ";
            std::cin >> nombreGrupo;
            std::cout << "Nombre del integrante a eliminar: ";
            std::cin >> nombre;
            std::cout << (lista.eliminarIntegrante(nombreGrupo, nombre)
                              ? "Integrante eliminado.\n"
                              : "No se encontro el grupo o el integrante.\n");

        } else if (opcion == 5) {
            lista.mostrar();

        } else if (opcion == 6) {
            lista.graficar();
        }
    } while (opcion != 0);

    return 0;
}