#ifndef LISTA_CIRCULAR_SIMPLE_H
#define LISTA_CIRCULAR_SIMPLE_H

#include <cstddef>
#include <string>

class ListaCircularSimple {
public:
    ListaCircularSimple();
    ~ListaCircularSimple();

    ListaCircularSimple(const ListaCircularSimple&) = delete;
    ListaCircularSimple& operator=(const ListaCircularSimple&) = delete;

    void insertar(const std::string& nombre, int edad);
    bool eliminar(const std::string& nombre);
    [[nodiscard]] std::size_t obtenerTamano() const;
    [[nodiscard]] bool estaVacia() const;
    void mostrar() const;
    void graficar() const;

private:
    struct Nodo {
        std::string nombre;
        int edad;
        Nodo* siguiente;
    };

    Nodo* cabeza;
    std::size_t tamano;
};

#endif
