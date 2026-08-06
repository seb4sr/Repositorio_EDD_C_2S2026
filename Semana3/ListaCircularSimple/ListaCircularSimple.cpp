#include "ListaCircularSimple.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

ListaCircularSimple::ListaCircularSimple()
    : cabeza(nullptr), tamano(0) {
}

ListaCircularSimple::~ListaCircularSimple() {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;
    do {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    } while (actual != cabeza);
}

void ListaCircularSimple::insertar(const std::string& nombre, int edad) {
    Nodo* nuevo = new Nodo{nombre, edad, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
    } else {
        Nodo* actual = cabeza;
        while (actual->siguiente != cabeza) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->siguiente = cabeza;
    }

    ++tamano;
}

bool ListaCircularSimple::eliminar(const std::string& nombre) {// nombre = 3
    if (cabeza == nullptr) {
        return false;
    }

    Nodo* actual = cabeza; //1
    Nodo* anterior = nullptr;

    do {                                // 
        if (actual->nombre == nombre) { // 1 - 2  - 4 - 5-!
            if (actual == cabeza) {
                if (actual->siguiente == cabeza) {
                    cabeza = nullptr;
                } else {
                    Nodo* ultimo = cabeza;
                    while (ultimo->siguiente != cabeza) {
                        ultimo = ultimo->siguiente;
                    }
                    cabeza = cabeza->siguiente;
                    ultimo->siguiente = cabeza;
                }
            } else {
                anterior->siguiente= actual->siguiente;
            }

            delete actual;
            --tamano;
            return true; // eliminacion satisfactoria
        }

        anterior = actual; // anterior =2
        actual = actual->siguiente; // actual = 3 / actual->siguiente = 4
    } while (actual != cabeza);

    return false;
}

std::size_t ListaCircularSimple::obtenerTamano() const {
    return tamano;
}

bool ListaCircularSimple::estaVacia() const {
    return cabeza == nullptr;
}

void ListaCircularSimple::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "La lista esta vacia.\n";
        return;
    }

    const Nodo* actual = cabeza;
    do {
        std::cout << actual->nombre << ", " << actual->edad << " anios\n";
        actual = actual->siguiente;
    } while (actual != cabeza);
}

void ListaCircularSimple::graficar() const {
    if (cabeza == nullptr) {
        std::cout << "La lista esta vacia, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("lista_circular_simple.dot");
    archivo << "digraph ListaCircularSimple {\n";
    archivo << "    rankdir=LR;\n"; // graficar LR de izquierda a derecha, y esta el TB que es de arriba a abajo que significa top to bottom
    archivo << "    node [shape=record, style=filled, fillcolor=\"#eaff06\"];\n";

    const Nodo* actual = cabeza;
    std::size_t i = 0;

    do {
        archivo << "    nodo" << i << " [label=\"{" << actual->nombre << " | "
                << actual->edad << " anios}\"];\n";
        actual = actual->siguiente;
        ++i;
    } while (actual != cabeza);

    for (std::size_t j = 0; j + 1 < i; ++j) {
        archivo << "    nodo" << j << " -> nodo" << j + 1 << ";\n";
    }
    archivo << "    nodo" << i - 1 << " -> nodo0;\n";

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng lista_circular_simple.dot -o lista_circular_simple.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: lista_circular_simple.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
