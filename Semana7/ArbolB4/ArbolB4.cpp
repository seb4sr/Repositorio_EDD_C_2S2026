#include "ArbolB4.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

ArbolB4::ArbolB4()
    : raiz(nullptr), cantidad(0) {
}

ArbolB4::~ArbolB4() {
    liberar(raiz);
}

ArbolB4::Nodo* ArbolB4::crearNodo(bool esHoja) {
    Nodo* nodo = new Nodo();
    nodo->cantidadClaves = 0;
    nodo->esHoja = esHoja;
    for (int i = 0; i < ORDEN; ++i) {
        nodo->hijos[i] = nullptr;
    }
    return nodo;
}

void ArbolB4::liberar(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->cantidadClaves; ++i) {
            liberar(nodo->hijos[i]);
        }
    }
    delete nodo;
}

void ArbolB4::dividirHijo(Nodo* padre, int indice) {
    Nodo* hijoLleno = padre->hijos[indice];
    Nodo* nuevoHijo = crearNodo(hijoLleno->esHoja);

    const int medio = MAX_CLAVES / 2;

    nuevoHijo->cantidadClaves = MAX_CLAVES - medio - 1;
    for (int j = 0; j < nuevoHijo->cantidadClaves; ++j) {
        nuevoHijo->edades[j] = hijoLleno->edades[medio + 1 + j];
        nuevoHijo->nombres[j] = hijoLleno->nombres[medio + 1 + j];
    }

    if (!hijoLleno->esHoja) {
        for (int j = 0; j <= nuevoHijo->cantidadClaves; ++j) {
            nuevoHijo->hijos[j] = hijoLleno->hijos[medio + 1 + j];
        }
    }

    int edadAscendida = hijoLleno->edades[medio];
    std::string nombreAscendido = hijoLleno->nombres[medio];

    hijoLleno->cantidadClaves = medio;

    for (int j = padre->cantidadClaves; j > indice; --j) {
        padre->hijos[j + 1] = padre->hijos[j];
    }
    padre->hijos[indice + 1] = nuevoHijo;

    for (int j = padre->cantidadClaves - 1; j >= indice; --j) {
        padre->edades[j + 1] = padre->edades[j];
        padre->nombres[j + 1] = padre->nombres[j];
    }
    padre->edades[indice] = edadAscendida;
    padre->nombres[indice] = nombreAscendido;

    ++padre->cantidadClaves;
}

void ArbolB4::insertarEnNodoNoLleno(Nodo* nodo, const std::string& nombre, int edad) {
    int i = nodo->cantidadClaves - 1;

    if (nodo->esHoja) {
        while (i >= 0 && edad < nodo->edades[i]) {
            nodo->edades[i + 1] = nodo->edades[i];
            nodo->nombres[i + 1] = nodo->nombres[i];
            --i;
        }
        nodo->edades[i + 1] = edad;
        nodo->nombres[i + 1] = nombre;
        ++nodo->cantidadClaves;
    } else {
        while (i >= 0 && edad < nodo->edades[i]) {
            --i;
        }
        ++i;

        if (nodo->hijos[i]->cantidadClaves == MAX_CLAVES) {
            dividirHijo(nodo, i);
            if (edad > nodo->edades[i]) {
                ++i;
            }
        }
        insertarEnNodoNoLleno(nodo->hijos[i], nombre, edad);
    }
}

bool ArbolB4::insertar(const std::string& nombre, int edad) {
    if (buscar(edad)) {
        return false;
    }

    if (raiz == nullptr) {
        raiz = crearNodo(true);
    }

    if (raiz->cantidadClaves == MAX_CLAVES) {
        Nodo* nuevaRaiz = crearNodo(false);
        nuevaRaiz->hijos[0] = raiz;
        dividirHijo(nuevaRaiz, 0);
        raiz = nuevaRaiz;
    }

    insertarEnNodoNoLleno(raiz, nombre, edad);
    ++cantidad;
    return true;
}

ArbolB4::Nodo* ArbolB4::buscar(Nodo* nodo, int edad) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    int i = 0;
    while (i < nodo->cantidadClaves && edad > nodo->edades[i]) {
        ++i;
    }

    if (i < nodo->cantidadClaves && nodo->edades[i] == edad) {
        return nodo;
    }

    if (nodo->esHoja) {
        return nullptr;
    }

    return buscar(nodo->hijos[i], edad);
}

bool ArbolB4::buscar(int edad) const {
    return buscar(raiz, edad) != nullptr;
}

ArbolB4::Nodo* ArbolB4::obtenerMaximoNodo(Nodo* nodo) const {
    while (!nodo->esHoja) {
        nodo = nodo->hijos[nodo->cantidadClaves];
    }
    return nodo;
}

ArbolB4::Nodo* ArbolB4::obtenerMinimoNodo(Nodo* nodo) const {
    while (!nodo->esHoja) {
        nodo = nodo->hijos[0];
    }
    return nodo;
}

void ArbolB4::prestarDeIzquierda(Nodo* nodo, int indice) {
    Nodo* hijo = nodo->hijos[indice];
    Nodo* hermanoIzq = nodo->hijos[indice - 1];

    for (int j = hijo->cantidadClaves - 1; j >= 0; --j) {
        hijo->edades[j + 1] = hijo->edades[j];
        hijo->nombres[j + 1] = hijo->nombres[j];
    }
    if (!hijo->esHoja) {
        for (int j = hijo->cantidadClaves; j >= 0; --j) {
            hijo->hijos[j + 1] = hijo->hijos[j];
        }
    }

    hijo->edades[0] = nodo->edades[indice - 1];
    hijo->nombres[0] = nodo->nombres[indice - 1];

    if (!hijo->esHoja) {
        hijo->hijos[0] = hermanoIzq->hijos[hermanoIzq->cantidadClaves];
    }

    nodo->edades[indice - 1] = hermanoIzq->edades[hermanoIzq->cantidadClaves - 1];
    nodo->nombres[indice - 1] = hermanoIzq->nombres[hermanoIzq->cantidadClaves - 1];

    ++hijo->cantidadClaves;
    --hermanoIzq->cantidadClaves;
}

void ArbolB4::prestarDeDerecha(Nodo* nodo, int indice) {
    Nodo* hijo = nodo->hijos[indice];
    Nodo* hermanoDer = nodo->hijos[indice + 1];

    hijo->edades[hijo->cantidadClaves] = nodo->edades[indice];
    hijo->nombres[hijo->cantidadClaves] = nodo->nombres[indice];

    if (!hijo->esHoja) {
        hijo->hijos[hijo->cantidadClaves + 1] = hermanoDer->hijos[0];
    }

    nodo->edades[indice] = hermanoDer->edades[0];
    nodo->nombres[indice] = hermanoDer->nombres[0];

    for (int j = 0; j < hermanoDer->cantidadClaves - 1; ++j) {
        hermanoDer->edades[j] = hermanoDer->edades[j + 1];
        hermanoDer->nombres[j] = hermanoDer->nombres[j + 1];
    }
    if (!hermanoDer->esHoja) {
        for (int j = 0; j < hermanoDer->cantidadClaves; ++j) {
            hermanoDer->hijos[j] = hermanoDer->hijos[j + 1];
        }
    }

    ++hijo->cantidadClaves;
    --hermanoDer->cantidadClaves;
}

void ArbolB4::fusionarHijos(Nodo* nodo, int indice) {
    Nodo* izquierdo = nodo->hijos[indice];
    Nodo* derecho = nodo->hijos[indice + 1];

    izquierdo->edades[izquierdo->cantidadClaves] = nodo->edades[indice];
    izquierdo->nombres[izquierdo->cantidadClaves] = nodo->nombres[indice];

    for (int j = 0; j < derecho->cantidadClaves; ++j) {
        izquierdo->edades[izquierdo->cantidadClaves + 1 + j] = derecho->edades[j];
        izquierdo->nombres[izquierdo->cantidadClaves + 1 + j] = derecho->nombres[j];
    }
    if (!izquierdo->esHoja) {
        for (int j = 0; j <= derecho->cantidadClaves; ++j) {
            izquierdo->hijos[izquierdo->cantidadClaves + 1 + j] = derecho->hijos[j];
        }
    }

    izquierdo->cantidadClaves += derecho->cantidadClaves + 1;
    delete derecho;

    for (int j = indice; j < nodo->cantidadClaves - 1; ++j) {
        nodo->edades[j] = nodo->edades[j + 1];
        nodo->nombres[j] = nodo->nombres[j + 1];
    }
    for (int j = indice + 1; j < nodo->cantidadClaves; ++j) {
        nodo->hijos[j] = nodo->hijos[j + 1];
    }

    --nodo->cantidadClaves;
}

int ArbolB4::llenarHijo(Nodo* nodo, int indice) {
    if (indice > 0 && nodo->hijos[indice - 1]->cantidadClaves > MIN_CLAVES) {
        prestarDeIzquierda(nodo, indice);
        return indice;
    }
    if (indice < nodo->cantidadClaves && nodo->hijos[indice + 1]->cantidadClaves > MIN_CLAVES) {
        prestarDeDerecha(nodo, indice);
        return indice;
    }
    if (indice < nodo->cantidadClaves) {
        fusionarHijos(nodo, indice);
        return indice;
    }
    fusionarHijos(nodo, indice - 1);
    return indice - 1;
}

void ArbolB4::eliminarDeNodoInterno(Nodo* nodo, int i) {
    int edadClave = nodo->edades[i];

    if (nodo->hijos[i]->cantidadClaves > MIN_CLAVES) {
        Nodo* predNodo = obtenerMaximoNodo(nodo->hijos[i]);
        int edadPred = predNodo->edades[predNodo->cantidadClaves - 1];
        std::string nombrePred = predNodo->nombres[predNodo->cantidadClaves - 1];

        nodo->edades[i] = edadPred;
        nodo->nombres[i] = nombrePred;
        eliminarDeNodo(nodo->hijos[i], edadPred);
    } else if (nodo->hijos[i + 1]->cantidadClaves > MIN_CLAVES) {
        Nodo* sucNodo = obtenerMinimoNodo(nodo->hijos[i + 1]);
        int edadSuc = sucNodo->edades[0];
        std::string nombreSuc = sucNodo->nombres[0];

        nodo->edades[i] = edadSuc;
        nodo->nombres[i] = nombreSuc;
        eliminarDeNodo(nodo->hijos[i + 1], edadSuc);
    } else {
        fusionarHijos(nodo, i);
        eliminarDeNodo(nodo->hijos[i], edadClave);
    }
}

void ArbolB4::eliminarDeNodo(Nodo* nodo, int edad) {
    int i = 0;
    while (i < nodo->cantidadClaves && edad > nodo->edades[i]) {
        ++i;
    }

    if (i < nodo->cantidadClaves && nodo->edades[i] == edad) {
        if (nodo->esHoja) {
            for (int j = i; j < nodo->cantidadClaves - 1; ++j) {
                nodo->edades[j] = nodo->edades[j + 1];
                nodo->nombres[j] = nodo->nombres[j + 1];
            }
            --nodo->cantidadClaves;
        } else {
            eliminarDeNodoInterno(nodo, i);
        }
        return;
    }

    if (nodo->hijos[i]->cantidadClaves == MIN_CLAVES) {
        i = llenarHijo(nodo, i);
    }
    eliminarDeNodo(nodo->hijos[i], edad);
}

bool ArbolB4::eliminar(int edad) {
    if (raiz == nullptr || !buscar(edad)) {
        return false;
    }

    eliminarDeNodo(raiz, edad);

    if (raiz->cantidadClaves == 0) {
        Nodo* raizVieja = raiz;
        raiz = raiz->esHoja ? nullptr : raiz->hijos[0];
        delete raizVieja;
    }

    --cantidad;
    return true;
}

std::size_t ArbolB4::obtenerCantidad() const {
    return cantidad;
}

bool ArbolB4::estaVacia() const {
    return raiz == nullptr;
}

int ArbolB4::altura(Nodo* nodo) const {
    if (nodo == nullptr) {
        return -1;
    }
    int h = 0;
    while (!nodo->esHoja) {
        nodo = nodo->hijos[0];
        ++h;
    }
    return h;
}

int ArbolB4::obtenerAltura() const {
    return altura(raiz);
}

void ArbolB4::mostrarEnOrden(Nodo* nodo) const {
    if (nodo == nullptr) {
        return;
    }

    int i = 0;
    for (; i < nodo->cantidadClaves; ++i) {
        if (!nodo->esHoja) {
            mostrarEnOrden(nodo->hijos[i]);
        }
        std::cout << "  " << nodo->nombres[i] << ", " << nodo->edades[i] << " anios\n";
    }
    if (!nodo->esHoja) {
        mostrarEnOrden(nodo->hijos[i]);
    }
}

void ArbolB4::mostrarEnOrden() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    std::cout << "En orden (edades ascendentes):\n";
    mostrarEnOrden(raiz);
}

std::size_t ArbolB4::generarNodosDot(Nodo* nodo, std::ofstream& archivo, std::size_t& contador) const {
    std::size_t idPropio = contador++;

    std::string label;
    if (nodo->esHoja) {
        for (int i = 0; i < nodo->cantidadClaves; ++i) {
            if (i > 0) {
                label += " | ";
            }
            label += nodo->nombres[i] + "," + std::to_string(nodo->edades[i]);
        }
    } else {
        for (int i = 0; i < nodo->cantidadClaves; ++i) {
            label += "<p" + std::to_string(i) + "> | ";
            label += nodo->nombres[i] + "," + std::to_string(nodo->edades[i]) + " | ";
        }
        label += "<p" + std::to_string(nodo->cantidadClaves) + ">";
    }

    archivo << "    n" << idPropio << " [label=\"" << label << "\"];\n";

    if (!nodo->esHoja) {
        for (int i = 0; i <= nodo->cantidadClaves; ++i) {
            std::size_t idHijo = generarNodosDot(nodo->hijos[i], archivo, contador);
            archivo << "    n" << idPropio << ":p" << i << " -> n" << idHijo << ";\n";
        }
    }

    return idPropio;
}

void ArbolB4::graficar() const {
    if (raiz == nullptr) {
        std::cout << "El arbol esta vacio, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("arbol_b4.dot");
    archivo << "digraph ArbolB4 {\n";
    archivo << "    node [shape=record, style=filled, fillcolor=\"#9ad0f5\"];\n";

    std::size_t contador = 0;
    generarNodosDot(raiz, archivo, contador);

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng arbol_b4.dot -o arbol_b4.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: arbol_b4.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}
