#include "ListaCircularDoble.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

ListaCircularDoble::ListaCircularDoble()
    : cabeza(nullptr), tamano(0) {
}

ListaCircularDoble::~ListaCircularDoble() {
    if (cabeza == nullptr) return;

    Nodo* actual = cabeza;
    do {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    } while (actual != cabeza);
}

void ListaCircularDoble::insertar(const std::string& nombre, int edad) {
    Nodo* nuevo = new Nodo{nombre, edad, nullptr, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        Nodo* ultimo = cabeza->anterior;
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }

    ++tamano;
}

bool ListaCircularDoble::eliminar(const std::string& nombre) {
    if (cabeza == nullptr) {
        return false;
    }

    Nodo* actual = cabeza;
    do {
        if (actual->nombre == nombre) {
            if (actual == cabeza && actual->siguiente == cabeza) {
                cabeza = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }
            }

            delete actual;
            --tamano;
            return true;
        }

        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

std::size_t ListaCircularDoble::obtenerTamano() const {
    return tamano;
}

bool ListaCircularDoble::estaVacia() const {
    return cabeza == nullptr;
}

void ListaCircularDoble::mostrar() const {
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

void ListaCircularDoble::mostrarInverso() const {
    if (cabeza == nullptr) {
        std::cout << "La lista esta vacia.\n";
        return;
    }

    const Nodo* actual = cabeza->anterior;
    do {
        std::cout << actual->nombre << ", " << actual->edad << " anios\n";
        actual = actual->anterior;
    } while (actual != cabeza->anterior);
}

void ListaCircularDoble::graficar() const {
    if (cabeza == nullptr) {
        std::cout << "La lista esta vacia, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("lista_circular_doble.dot");
    archivo << "digraph ListaCircularDoble {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [shape=record, style=filled, fillcolor=\"#ff2f2f\"];\n";

    const Nodo* actual = cabeza;
    std::size_t i = 0;

    do {
        archivo << "    nodo" << i << " [label=\"{" << actual->nombre << " | "
                << actual->edad << " anios}\"];\n";
        actual = actual->siguiente;
        ++i;
    } while (actual != cabeza);

    for (std::size_t j = 0; j + 1 < i; ++j) {
        archivo << "    nodo" << j << " -> nodo" << j + 1 << " [dir=both];\n";
    }
    archivo << "    nodo" << i - 1 << " -> nodo0 [dir=both];\n";

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng lista_circular_doble.dot -o lista_circular_doble.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: lista_circular_doble.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
