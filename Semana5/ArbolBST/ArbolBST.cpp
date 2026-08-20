#include "ArbolBST.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

ArbolBST::ArbolBST()
    : raiz(nullptr), cantidad(0) {
}

ArbolBST::~ArbolBST() {
    liberar(raiz);
}

void ArbolBST::liberar(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->izquierdo);
    liberar(nodo->derecho);
    delete nodo;
}

ArbolBST::Nodo* ArbolBST::insertar(Nodo* nodo, const std::string& nombre, int edad, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new Nodo{nombre, edad, nullptr, nullptr};
    }

    if (edad < nodo->edad) {
        nodo->izquierdo = insertar(nodo->izquierdo, nombre, edad, insertado);
    } else if (edad > nodo->edad) {
        nodo->derecho = insertar(nodo->derecho, nombre, edad, insertado);
    } else {
        insertado = false;
    }

    return nodo;
}

bool ArbolBST::insertar(const std::string& nombre, int edad) {
    bool insertado = false;
    raiz = insertar(raiz, nombre, edad, insertado);
    if (insertado) {
        ++cantidad;
    }
    return insertado;
}

ArbolBST::Nodo* ArbolBST::encontrarMinimo(Nodo* nodo) const {
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

ArbolBST::Nodo* ArbolBST::eliminar(Nodo* nodo, int edad, bool& eliminado) {
    if (nodo == nullptr) {
        eliminado = false;
        return nullptr;
    }

    if (edad < nodo->edad) {
        nodo->izquierdo = eliminar(nodo->izquierdo, edad, eliminado);
    } else if (edad > nodo->edad) {
        nodo->derecho = eliminar(nodo->derecho, edad, eliminado);
    } else {
        eliminado = true;

        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            delete nodo;
            return nullptr;
        }

        if (nodo->izquierdo == nullptr) {
            Nodo* hijo = nodo->derecho;
            delete nodo;
            return hijo;
        }

        if (nodo->derecho == nullptr) {
            Nodo* hijo = nodo->izquierdo;
            delete nodo;
            return hijo;
        }

        Nodo* sucesor = encontrarMinimo(nodo->derecho);
        nodo->nombre = sucesor->nombre;
        nodo->edad = sucesor->edad;

        bool eliminadoSucesor = false;
        nodo->derecho = eliminar(nodo->derecho, sucesor->edad, eliminadoSucesor);
    }

    return nodo;
}

bool ArbolBST::eliminar(int edad) {
    bool eliminado = false;
    raiz = eliminar(raiz, edad, eliminado);
    if (eliminado) {
        --cantidad;
    }
    return eliminado;
}

ArbolBST::Nodo* ArbolBST::buscar(Nodo* nodo, int edad) const {
    if (nodo == nullptr || nodo->edad == edad) {
        return nodo;
    }

    if (edad < nodo->edad) {
        return buscar(nodo->izquierdo, edad);
    }
    return buscar(nodo->derecho, edad);
}

bool ArbolBST::buscar(int edad) const {
    return buscar(raiz, edad) != nullptr;
}

std::size_t ArbolBST::obtenerCantidad() const {
    return cantidad;
}

bool ArbolBST::estaVacia() const {
    return raiz == nullptr;
}

int ArbolBST::altura(Nodo* nodo) const {
    if (nodo == nullptr) {
        return -1;
    }
    return 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));
}

int ArbolBST::obtenerAltura() const {
    return altura(raiz);
}

void ArbolBST::mostrarEnOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    mostrarEnOrden(nodo->izquierdo);
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
    mostrarEnOrden(nodo->derecho);
}

void ArbolBST::mostrarEnOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "En orden (edades ascendentes):\n";
    mostrarEnOrden(raiz);
}

void ArbolBST::mostrarPreOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
    mostrarPreOrden(nodo->izquierdo);
    mostrarPreOrden(nodo->derecho);
}

void ArbolBST::mostrarPreOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "Preorden (raiz primero):\n";
    mostrarPreOrden(raiz);
}

void ArbolBST::mostrarPostOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    mostrarPostOrden(nodo->izquierdo);
    mostrarPostOrden(nodo->derecho);
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
}

void ArbolBST::mostrarPostOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "Postorden (raiz al final):\n";
    mostrarPostOrden(raiz);
}

std::size_t ArbolBST::generarNodosDot(Nodo* nodo, std::ofstream& archivo, std::size_t& contador) const {
    std::size_t idPropio = contador++;
    archivo << "    n" << idPropio << " [label=\"{" << nodo->nombre
            << " | " << nodo->edad << " anios}\"];\n";

    if (nodo->izquierdo != nullptr) {
        std::size_t idIzquierdo = generarNodosDot(nodo->izquierdo, archivo, contador);
        archivo << "    n" << idPropio << " -> n" << idIzquierdo << " [label=\"I\"];\n";
    }
    if (nodo->derecho != nullptr) {
        std::size_t idDerecho = generarNodosDot(nodo->derecho, archivo, contador);
        archivo << "    n" << idPropio << " -> n" << idDerecho << " [label=\"D\"];\n";
    }

    return idPropio;
}

void ArbolBST::graficar() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("arbol_bst.dot");
    archivo << "digraph ArbolBST {\n";
    archivo << "    node [shape=record, style=filled, fillcolor=\"#9ad0f5\"];\n";

    std::size_t contador = 0;
    generarNodosDot(raiz, archivo, contador);

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng arbol_bst.dot -o arbol_bst.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: arbol_bst.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
