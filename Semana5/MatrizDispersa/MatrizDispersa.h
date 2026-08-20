#ifndef MATRIZ_DISPERSA_H
#define MATRIZ_DISPERSA_H

#include <cstddef>

class MatrizDispersa {
public:
    MatrizDispersa();
    ~MatrizDispersa();

    MatrizDispersa(const MatrizDispersa&) = delete;
    MatrizDispersa& operator=(const MatrizDispersa&) = delete;

    bool insertarValor(int fila, int columna, int valor);
    bool eliminarValor(int fila, int columna);
    [[nodiscard]] int obtenerValor(int fila, int columna) const;
    [[nodiscard]] std::size_t obtenerCantidadValores() const;
    [[nodiscard]] bool estaVacia() const;
    void mostrar() const;
    void graficar() const;

private:
    struct NodoDato {
        int fila;
        int columna;
        int valor; // atributos que ustedes necesitan
        NodoDato* derecha;
        NodoDato* abajo;
    };

    struct NodoCabeceraFila {
        int fila;
        NodoDato* primerDato;
        NodoCabeceraFila* siguiente;
    };

    struct NodoCabeceraColumna {
        int columna;
        NodoDato* primerDato;
        NodoCabeceraColumna* siguiente;
    };

    NodoCabeceraFila* buscarFila(int fila) const;
    NodoCabeceraColumna* buscarColumna(int columna) const;
    NodoCabeceraFila* buscarOCrearFila(int fila);
    NodoCabeceraColumna* buscarOCrearColumna(int columna);

    NodoCabeceraFila* cabezaFilas;
    NodoCabeceraColumna* cabezaColumnas;
    std::size_t cantidadValores;
};

#endif
