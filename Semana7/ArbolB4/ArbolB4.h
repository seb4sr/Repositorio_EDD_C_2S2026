#ifndef ARBOL_B4_H
#define ARBOL_B4_H

#include <cstddef>
#include <iosfwd>
#include <string>

class ArbolB4 {
public:
    ArbolB4();
    ~ArbolB4();

    ArbolB4(const ArbolB4&) = delete;
    ArbolB4& operator=(const ArbolB4&) = delete;

    bool insertar(const std::string& nombre, int edad);
    bool eliminar(int edad);
    [[nodiscard]] bool buscar(int edad) const;
    [[nodiscard]] std::size_t obtenerCantidad() const;
    [[nodiscard]] bool estaVacia() const;
    [[nodiscard]] int obtenerAltura() const;
    void mostrarEnOrden() const;
    void graficar() const;

private:
    static constexpr int ORDEN = 4;
    static constexpr int MAX_CLAVES = ORDEN - 1;
    static constexpr int MIN_CLAVES = (ORDEN + 1) / 2 - 1;

    struct Nodo {
        int cantidadClaves;
        std::string nombres[MAX_CLAVES];
        int edades[MAX_CLAVES];
        Nodo* hijos[ORDEN];
        bool esHoja;
    };

    Nodo* crearNodo(bool esHoja);
    void liberar(Nodo* nodo);

    void insertarEnNodoNoLleno(Nodo* nodo, const std::string& nombre, int edad);
    void dividirHijo(Nodo* padre, int indice);

    Nodo* buscar(Nodo* nodo, int edad) const;

    void eliminarDeNodo(Nodo* nodo, int edad);
    void eliminarDeNodoInterno(Nodo* nodo, int indice);
    int llenarHijo(Nodo* nodo, int indice);
    void prestarDeIzquierda(Nodo* nodo, int indice);
    void prestarDeDerecha(Nodo* nodo, int indice);
    void fusionarHijos(Nodo* nodo, int indice);
    Nodo* obtenerMaximoNodo(Nodo* nodo) const;
    Nodo* obtenerMinimoNodo(Nodo* nodo) const;

    int altura(Nodo* nodo) const;
    void mostrarEnOrden(Nodo* nodo) const;
    std::size_t generarNodosDot(Nodo* nodo, std::ofstream& archivo, std::size_t& contador) const;

    Nodo* raiz;
    std::size_t cantidad;
};

#endif
