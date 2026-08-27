#include "ArbolAVL.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

ArbolAVL::ArbolAVL()
    : raiz(nullptr), cantidad(0) {
}

ArbolAVL::~ArbolAVL() {
    liberar(raiz);
}

void ArbolAVL::liberar(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->izquierdo);
    liberar(nodo->derecho);
    delete nodo;
}

int ArbolAVL::altura(Nodo* nodo) const {
    return nodo == nullptr ? -1 : nodo->altura;
}

void ArbolAVL::actualizarAltura(Nodo* nodo) {
    nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));
}

int ArbolAVL::factorBalance(Nodo* nodo) const {
    return nodo == nullptr ? 0 : altura(nodo->izquierdo) - altura(nodo->derecho);
}

ArbolAVL::Nodo* ArbolAVL::rotarDerecha(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->izquierdo;
    Nodo* subarbolMovido = nuevaRaiz->derecho;

    nuevaRaiz->derecho = nodo;
    nodo->izquierdo = subarbolMovido;

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

ArbolAVL::Nodo* ArbolAVL::rotarIzquierda(Nodo* nodo) {
    Nodo* nuevaRaiz = nodo->derecho;
    Nodo* subarbolMovido = nuevaRaiz->izquierdo;

    nuevaRaiz->izquierdo = nodo;
    nodo->derecho = subarbolMovido;

    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

ArbolAVL::Nodo* ArbolAVL::balancear(Nodo* nodo) {
    actualizarAltura(nodo);
    int balance = factorBalance(nodo);

    if (balance > 1 && factorBalance(nodo->izquierdo) >= 0) {
        return rotarDerecha(nodo);
    }
    if (balance > 1 && factorBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && factorBalance(nodo->derecho) <= 0) {
        return rotarIzquierda(nodo);
    }
    if (balance < -1 && factorBalance(nodo->derecho) > 0) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

ArbolAVL::Nodo* ArbolAVL::insertar(Nodo* nodo, const std::string& nombre, int edad, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new Nodo{nombre, edad, 0, nullptr, nullptr};
    }

    if (edad < nodo->edad) {
        nodo->izquierdo = insertar(nodo->izquierdo, nombre, edad, insertado);
    } else if (edad > nodo->edad) {
        nodo->derecho = insertar(nodo->derecho, nombre, edad, insertado);
    } else {
        insertado = false;
        return nodo;
    }

    return balancear(nodo);
}

bool ArbolAVL::insertar(const std::string& nombre, int edad) {
    bool insertado = false;
    raiz = insertar(raiz, nombre, edad, insertado);
    if (insertado) {
        ++cantidad;
    }
    return insertado;
}

ArbolAVL::Nodo* ArbolAVL::encontrarMinimo(Nodo* nodo) const {
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

ArbolAVL::Nodo* ArbolAVL::eliminar(Nodo* nodo, int edad, bool& eliminado) {
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

    return balancear(nodo);
}

bool ArbolAVL::eliminar(int edad) {
    bool eliminado = false;
    raiz = eliminar(raiz, edad, eliminado);
    if (eliminado) {
        --cantidad;
    }
    return eliminado;
}

ArbolAVL::Nodo* ArbolAVL::buscar(Nodo* nodo, int edad) const {
    if (nodo == nullptr || nodo->edad == edad) {
        return nodo;
    }

    if (edad < nodo->edad) {
        return buscar(nodo->izquierdo, edad);
    }
    return buscar(nodo->derecho, edad);
}

bool ArbolAVL::buscar(int edad) const {
    return buscar(raiz, edad) != nullptr;
}

std::size_t ArbolAVL::obtenerCantidad() const {
    return cantidad;
}

bool ArbolAVL::estaVacia() const {
    return raiz == nullptr;
}

int ArbolAVL::obtenerAltura() const {
    return altura(raiz);
}

void ArbolAVL::mostrarEnOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    mostrarEnOrden(nodo->izquierdo);
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
    mostrarEnOrden(nodo->derecho);
}

void ArbolAVL::mostrarEnOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "En orden (edades ascendentes):\n";
    mostrarEnOrden(raiz);
}

void ArbolAVL::mostrarPreOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
    mostrarPreOrden(nodo->izquierdo);
    mostrarPreOrden(nodo->derecho);
}

void ArbolAVL::mostrarPreOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "Preorden (raiz primero):\n";
    mostrarPreOrden(raiz);
}

void ArbolAVL::mostrarPostOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }
    mostrarPostOrden(nodo->izquierdo);
    mostrarPostOrden(nodo->derecho);
    std::cout << "  " << nodo->nombre << ", " << nodo->edad << " anios\n";
}

void ArbolAVL::mostrarPostOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "Postorden (raiz al final):\n";
    mostrarPostOrden(raiz);
}

std::size_t ArbolAVL::generarNodosDot(Nodo* nodo, std::ofstream& archivo, std::size_t& contador) const {
    std::size_t idPropio = contador++;
    archivo << "    n" << idPropio << " [label=\"{" << nodo->nombre << " | " << nodo->edad
            << " anios | fb=" << factorBalance(nodo) << "}\"];\n";

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

void ArbolAVL::graficar() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("arbol_avl.dot");
    archivo << "digraph ArbolAVL {\n";
    archivo << "    node [shape=record, style=filled, fillcolor=\"#9ad0f5\"];\n";

    std::size_t contador = 0;
    generarNodosDot(raiz, archivo, contador);

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng arbol_avl.dot -o arbol_avl.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: arbol_avl.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
