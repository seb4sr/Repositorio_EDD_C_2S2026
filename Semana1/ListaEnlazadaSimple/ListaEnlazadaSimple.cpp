#include "ListaEnlazadaSimple.h"

#include <iostream>

ListaEnlazadaSimple::ListaEnlazadaSimple()
    : cabeza(nullptr), tamano(0) {
}

ListaEnlazadaSimple::~ListaEnlazadaSimple() {
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        Nodo* nodo_a_eliminar = actual;
        actual = actual->siguiente;
        delete nodo_a_eliminar;
    }
}

void ListaEnlazadaSimple::insertar(int valor) {
    Nodo* nuevo_nodo = new Nodo{valor, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevo_nodo;
        ++tamano;
        return;
    }

    Nodo* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo_nodo;
    ++tamano;
}

bool ListaEnlazadaSimple::eliminar(int valor) {//valor a eliminar es 3
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

        // 1->2->3->4->
    while (actual != nullptr && actual->valor != valor) {
        
        anterior = actual; 
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        return false;
    }

    if (anterior == nullptr) {
        cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    } 

    delete actual;
    --tamano;
    return true;
}

std::size_t ListaEnlazadaSimple::obtenerTamano() const {
    return tamano;
}

bool ListaEnlazadaSimple::estaVacia() const {
    return cabeza == nullptr;
}

void ListaEnlazadaSimple::imprimir() const {
    if (estaVacia()) {
        std::cout << "Lista vacia\n";
        return;
    }

    const Nodo* actual = cabeza;
    std::cout << "Cabeza -> ";

    while (actual != nullptr) {
        std::cout << actual->valor << " -> ";
        actual = actual->siguiente;
    }

    std::cout << "nullptr\n";
}
