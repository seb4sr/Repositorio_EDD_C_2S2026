#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include <cstddef>
#include <iosfwd>
#include <string>

class ArbolAVL {
public:
    ArbolAVL();
    ~ArbolAVL();

    ArbolAVL(const ArbolAVL&) = delete;
    ArbolAVL& operator=(const ArbolAVL&) = delete;

    bool insertar(const std::string& nombre, int edad);
    bool eliminar(int edad);
    [[nodiscard]] bool buscar(int edad) const;
    [[nodiscard]] std::size_t obtenerCantidad() const;
    [[nodiscard]] bool estaVacia() const;
    [[nodiscard]] int obtenerAltura() const;
    void mostrarEnOrden() const;
    void mostrarPreOrden() const;
    void mostrarPostOrden() const;
    void graficar() const;

private:
    struct Nodo {
        std::string nombre;
        int edad;
        int altura;
        Nodo* izquierdo;
        Nodo* derecho;
    };

    Nodo* insertar(Nodo* nodo, const std::string& nombre, int edad, bool& insertado);
    Nodo* eliminar(Nodo* nodo, int edad, bool& eliminado);
    Nodo* buscar(Nodo* nodo, int edad) const;
    Nodo* encontrarMinimo(Nodo* nodo) const;
    void liberar(Nodo* nodo);

    int altura(Nodo* nodo) const;
    void actualizarAltura(Nodo* nodo);
    int factorBalance(Nodo* nodo) const;
    Nodo* rotarDerecha(Nodo* nodo);
    Nodo* rotarIzquierda(Nodo* nodo);
    Nodo* balancear(Nodo* nodo);

    void mostrarEnOrden(Nodo* nodo) const;
    void mostrarPreOrden(Nodo* nodo) const;
    void mostrarPostOrden(Nodo* nodo) const;
    std::size_t generarNodosDot(Nodo* nodo, std::ofstream& archivo, std::size_t& contador) const;

    Nodo* raiz;
    std::size_t cantidad;
};

#endif
