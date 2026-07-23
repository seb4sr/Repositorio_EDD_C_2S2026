#ifndef LISTA_ENLAZADA_SIMPLE_H
#define LISTA_ENLAZADA_SIMPLE_H

#include <cstddef>

// Tipo de dato abstracto que representa una lista de numeros enteros.
class ListaEnlazadaSimple {
public:
    ListaEnlazadaSimple();
    ~ListaEnlazadaSimple();

    // Evita copias superficiales de los punteros internos.
    ListaEnlazadaSimple(const ListaEnlazadaSimple&) = delete;
    ListaEnlazadaSimple& operator=(const ListaEnlazadaSimple&) = delete;
    
    // Permite mover una lista a otra sin copiar sus nodos.
    void insertar(int valor);
    bool eliminar(int valor);
    [[nodiscard]] std::size_t obtenerTamano() const;
    [[nodiscard]] bool estaVacia() const;
    void imprimir() const;

private:
    struct Nodo {
        int valor;
        Nodo* siguiente;
    };

    Nodo* cabeza;
    std::size_t tamano;
};

#endif
