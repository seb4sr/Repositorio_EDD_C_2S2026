#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <cstddef>
#include <string>

class ListaCircularDoble {
public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    ListaCircularDoble(const ListaCircularDoble&) = delete;
    ListaCircularDoble& operator=(const ListaCircularDoble&) = delete;

    void insertar(const std::string& nombre, int edad);
    bool eliminar(const std::string& nombre);
    [[nodiscard]] std::size_t obtenerTamano() const;
    [[nodiscard]] bool estaVacia() const;
    void mostrar() const;
    void mostrarInverso() const;
    void graficar() const;

private:
    struct Nodo {
        std::string nombre;
        int edad;
        Nodo* siguiente;
        Nodo* anterior;
    };

    Nodo* cabeza;
    std::size_t tamano;
};

#endif
