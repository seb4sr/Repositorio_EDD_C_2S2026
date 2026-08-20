#include "MatrizDispersa.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

MatrizDispersa::MatrizDispersa()
    : cabezaFilas(nullptr), cabezaColumnas(nullptr), cantidadValores(0) {
}

MatrizDispersa::~MatrizDispersa() {
    NodoCabeceraFila* filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        NodoDato* datoActual = filaActual->primerDato;
        while (datoActual != nullptr) {
            NodoDato* datoAEliminar = datoActual;
            datoActual = datoActual->derecha;
            delete datoAEliminar;
        }

        NodoCabeceraFila* filaAEliminar = filaActual;
        filaActual = filaActual->siguiente;
        delete filaAEliminar;
    }

    NodoCabeceraColumna* columnaActual = cabezaColumnas;
    while (columnaActual != nullptr) {
        NodoCabeceraColumna* columnaAEliminar = columnaActual;
        columnaActual = columnaActual->siguiente;
        delete columnaAEliminar;
    }
}

MatrizDispersa::NodoCabeceraFila* MatrizDispersa::buscarFila(int fila) const {
    NodoCabeceraFila* actual = cabezaFilas;
    while (actual != nullptr && actual->fila != fila) {
        actual = actual->siguiente;
    }
    return actual;
}

MatrizDispersa::NodoCabeceraColumna* MatrizDispersa::buscarColumna(int columna) const {
    NodoCabeceraColumna* actual = cabezaColumnas;
    while (actual != nullptr && actual->columna != columna) {
        actual = actual->siguiente;
    }
    return actual;
}

MatrizDispersa::NodoCabeceraFila* MatrizDispersa::buscarOCrearFila(int fila) {
    NodoCabeceraFila* anterior = nullptr;
    NodoCabeceraFila* actual = cabezaFilas;
    while (actual != nullptr && actual->fila < fila) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr && actual->fila == fila) {
        return actual;
    }

    NodoCabeceraFila* nuevo = new NodoCabeceraFila{fila, nullptr, actual};
    if (anterior == nullptr) {
        cabezaFilas = nuevo;
    } else {
        anterior->siguiente = nuevo;
    }
    return nuevo;
}

MatrizDispersa::NodoCabeceraColumna* MatrizDispersa::buscarOCrearColumna(int columna) {
    NodoCabeceraColumna* anterior = nullptr;
    NodoCabeceraColumna* actual = cabezaColumnas;
    while (actual != nullptr && actual->columna < columna) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr && actual->columna == columna) {
        return actual;
    }

    NodoCabeceraColumna* nuevo = new NodoCabeceraColumna{columna, nullptr, actual};
    if (anterior == nullptr) {
        cabezaColumnas = nuevo;
    } else {
        anterior->siguiente = nuevo;
    }
    return nuevo;
}

bool MatrizDispersa::insertarValor(int fila, int columna, int valor) {
    if (valor == 0) {
        return false;
    }

    NodoCabeceraFila* cabFila = buscarOCrearFila(fila);
    NodoCabeceraColumna* cabColumna = buscarOCrearColumna(columna);

    NodoDato* anteriorEnFila = nullptr;
    NodoDato* actualEnFila = cabFila->primerDato;
    while (actualEnFila != nullptr && actualEnFila->columna < columna) {
        anteriorEnFila = actualEnFila;
        actualEnFila = actualEnFila->derecha;
    }

    if (actualEnFila != nullptr && actualEnFila->columna == columna) {
        actualEnFila->valor = valor;
        return true;
    }

    NodoDato* anteriorEnColumna = nullptr;
    NodoDato* actualEnColumna = cabColumna->primerDato;
    while (actualEnColumna != nullptr && actualEnColumna->fila < fila) {
        anteriorEnColumna = actualEnColumna;
        actualEnColumna = actualEnColumna->abajo;
    }

    NodoDato* nuevo = new NodoDato{fila, columna, valor, actualEnFila, actualEnColumna};

    if (anteriorEnFila == nullptr) {
        cabFila->primerDato = nuevo;
    } else {
        anteriorEnFila->derecha = nuevo;
    }

    if (anteriorEnColumna == nullptr) {
        cabColumna->primerDato = nuevo;
    } else {
        anteriorEnColumna->abajo = nuevo;
    }

    ++cantidadValores;
    return true;
}

bool MatrizDispersa::eliminarValor(int fila, int columna) {
    NodoCabeceraFila* cabFila = buscarFila(fila);
    NodoCabeceraColumna* cabColumna = buscarColumna(columna);
    if (cabFila == nullptr || cabColumna == nullptr) {
        return false;
    }

    NodoDato* anteriorEnFila = nullptr;
    NodoDato* actualEnFila = cabFila->primerDato;
    while (actualEnFila != nullptr && actualEnFila->columna < columna) {
        anteriorEnFila = actualEnFila;
        actualEnFila = actualEnFila->derecha;
    }
    if (actualEnFila == nullptr || actualEnFila->columna != columna) {
        return false;
    }

    NodoDato* anteriorEnColumna = nullptr;
    NodoDato* actualEnColumna = cabColumna->primerDato;
    while (actualEnColumna != nullptr && actualEnColumna->fila < fila) {
        anteriorEnColumna = actualEnColumna;
        actualEnColumna = actualEnColumna->abajo;
    }

    if (anteriorEnFila == nullptr) {
        cabFila->primerDato = actualEnFila->derecha;
    } else {
        anteriorEnFila->derecha = actualEnFila->derecha;
    }

    if (anteriorEnColumna == nullptr) {
        cabColumna->primerDato = actualEnColumna->abajo;
    } else {
        anteriorEnColumna->abajo = actualEnColumna->abajo;
    }

    delete actualEnFila;
    --cantidadValores;
    return true;
}

int MatrizDispersa::obtenerValor(int fila, int columna) const {
    NodoCabeceraFila* cabFila = buscarFila(fila);
    if (cabFila == nullptr) {
        return 0;
    }

    NodoDato* actual = cabFila->primerDato;
    while (actual != nullptr && actual->columna < columna) {
        actual = actual->derecha;
    }
    return (actual != nullptr && actual->columna == columna) ? actual->valor : 0;
}

std::size_t MatrizDispersa::obtenerCantidadValores() const {
    return cantidadValores;
}

bool MatrizDispersa::estaVacia() const {
    return cantidadValores == 0;
}

void MatrizDispersa::mostrar() const {
    if (cantidadValores == 0) {
        std::cout << "La matriz esta vacia (todos los valores son 0).\n";
        return;
    }

    const NodoCabeceraFila* filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        const NodoDato* datoActual = filaActual->primerDato;
        if (datoActual != nullptr) {
            std::cout << "Fila " << filaActual->fila << ":\n";
            while (datoActual != nullptr) {
                std::cout << "  columna " << datoActual->columna
                           << " = " << datoActual->valor << "\n";
                datoActual = datoActual->derecha;
            }
        }
        filaActual = filaActual->siguiente;
    }

    std::cout << "Total de valores no nulos: " << cantidadValores << "\n";
}

void MatrizDispersa::graficar() const {
    if (cantidadValores == 0) {
        std::cout << "La matriz esta vacia, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("matriz_dispersa.dot");
    archivo << "digraph MatrizDispersa {\n";
    archivo << "    labelloc=\"t\";\n";
    archivo << "    fontsize=16;\n";
    archivo << "    nodesep=0.6;\n";
    archivo << "    ranksep=0.7;\n";
    archivo << "    node [shape=box, style=filled, fontname=\"Arial\", fontsize=11];\n\n";

    archivo << "    origen [label=\"fila / columna\", shape=ellipse, fillcolor=\"#dddddd\", fontsize=10];\n\n";

    const NodoCabeceraColumna* columnaActual = cabezaColumnas;
    while (columnaActual != nullptr) {
        archivo << "    cab_col_" << columnaActual->columna << " [label=\"Col " << columnaActual->columna
                << "\", group=" << (columnaActual->columna + 1) << ", fillcolor=\"#2980b9\", fontcolor=white];\n";
        columnaActual = columnaActual->siguiente;
    }
    archivo << "\n";

    const NodoCabeceraFila* filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        archivo << "    cab_fil_" << filaActual->fila << " [label=\"Fil " << filaActual->fila
                << "\", group=0, fillcolor=\"#27ae60\", fontcolor=white];\n";
        filaActual = filaActual->siguiente;
    }
    archivo << "\n";

    filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        const NodoDato* dato = filaActual->primerDato;
        while (dato != nullptr) {
            archivo << "    dato_" << dato->fila << "_" << dato->columna
                    << " [label=\"(" << dato->fila << "," << dato->columna << ")\\nval=" << dato->valor
                    << "\", group=" << (dato->columna + 1) << ", fillcolor=\"#ecf0f1\"];\n";
            dato = dato->derecha;
        }
        filaActual = filaActual->siguiente;
    }
    archivo << "\n";

    filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        std::string anterior = "cab_fil_" + std::to_string(filaActual->fila);
        const NodoDato* dato = filaActual->primerDato;
        while (dato != nullptr) {
            std::string actual = "dato_" + std::to_string(dato->fila) + "_" + std::to_string(dato->columna);
            archivo << "    " << anterior << " -> " << actual << " [dir=both, color=\"#27ae60\"];\n";
            anterior = actual;
            dato = dato->derecha;
        }
        filaActual = filaActual->siguiente;
    }
    archivo << "\n";

    columnaActual = cabezaColumnas;
    while (columnaActual != nullptr) {
        std::string anterior = "cab_col_" + std::to_string(columnaActual->columna);
        const NodoDato* dato = columnaActual->primerDato;
        while (dato != nullptr) {
            std::string actual = "dato_" + std::to_string(dato->fila) + "_" + std::to_string(dato->columna);
            archivo << "    " << anterior << " -> " << actual << " [dir=both, color=\"#2980b9\"];\n";
            anterior = actual;
            dato = dato->abajo;
        }
        columnaActual = columnaActual->siguiente;
    }
    archivo << "\n";

    archivo << "    { rank=same; origen; ";
    columnaActual = cabezaColumnas;
    while (columnaActual != nullptr) {
        archivo << "cab_col_" << columnaActual->columna << "; ";
        columnaActual = columnaActual->siguiente;
    }
    archivo << "}\n";

    filaActual = cabezaFilas;
    while (filaActual != nullptr) {
        archivo << "    { rank=same; cab_fil_" << filaActual->fila << "; ";
        const NodoDato* dato = filaActual->primerDato;
        while (dato != nullptr) {
            archivo << "dato_" << dato->fila << "_" << dato->columna << "; ";
            dato = dato->derecha;
        }
        archivo << "}\n";
        filaActual = filaActual->siguiente;
    }

    if (cabezaColumnas != nullptr) {
        archivo << "\n    origen -> cab_col_" << cabezaColumnas->columna << " [style=invis];\n";
        const NodoCabeceraColumna* anterior = cabezaColumnas;
        const NodoCabeceraColumna* actual = cabezaColumnas->siguiente;
        while (actual != nullptr) {
            archivo << "    cab_col_" << anterior->columna << " -> cab_col_" << actual->columna
                    << " [style=invis];\n";
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    if (cabezaFilas != nullptr) {
        archivo << "\n    origen -> cab_fil_" << cabezaFilas->fila << " [style=invis];\n";
        const NodoCabeceraFila* anterior = cabezaFilas;
        const NodoCabeceraFila* actual = cabezaFilas->siguiente;
        while (actual != nullptr) {
            archivo << "    cab_fil_" << anterior->fila << " -> cab_fil_" << actual->fila
                    << " [style=invis];\n";
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng matriz_dispersa.dot -o matriz_dispersa.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: matriz_dispersa.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
