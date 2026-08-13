#include "ListaDeListas.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

ListaDeListas::ListaDeListas()
    : cabeza(nullptr), cantidadGrupos(0) {
}

ListaDeListas::~ListaDeListas() {
    NodoGrupo* grupoActual = cabeza;
    while (grupoActual != nullptr) {
        NodoIntegrante* integranteActual = grupoActual->cabezaIntegrantes;
        while (integranteActual != nullptr) {
            NodoIntegrante* integranteAEliminar = integranteActual;
            integranteActual = integranteActual->siguiente;
            delete integranteAEliminar;
        }

        NodoGrupo* grupoAEliminar = grupoActual;
        grupoActual = grupoActual->siguiente;
        delete grupoAEliminar;
    }
}

ListaDeListas::NodoGrupo* ListaDeListas::buscarGrupo(const std::string& nombreGrupo) const {
    NodoGrupo* actual = cabeza;
    while (actual != nullptr && actual->nombre != nombreGrupo) {
        actual = actual->siguiente;
    }
    return actual;
}

bool ListaDeListas::insertarGrupo(const std::string& nombreGrupo) {
    if (buscarGrupo(nombreGrupo) != nullptr) {
        return false;
    }

    NodoGrupo* nuevo = new NodoGrupo{nombreGrupo, nullptr, 0, nullptr};

    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        NodoGrupo* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    ++cantidadGrupos;
    return true;
}

bool ListaDeListas::insertarIntegrante(const std::string& nombreGrupo, const std::string& nombre, int edad) {
    NodoGrupo* grupo = buscarGrupo(nombreGrupo);
    if (grupo == nullptr) {
        return false;
    }

    NodoIntegrante* nuevo = new NodoIntegrante{nombre, edad, nullptr};

    if (grupo->cabezaIntegrantes == nullptr) {
        grupo->cabezaIntegrantes = nuevo;
    } else {
        NodoIntegrante* actual = grupo->cabezaIntegrantes;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    ++grupo->cantidadIntegrantes;
    return true;
}

bool ListaDeListas::eliminarGrupo(const std::string& nombreGrupo) {
    NodoGrupo* actual = cabeza;
    NodoGrupo* anterior = nullptr;

    while (actual != nullptr && actual->nombre != nombreGrupo) {
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

    NodoIntegrante* integranteActual = actual->cabezaIntegrantes;
    while (integranteActual != nullptr) {
        NodoIntegrante* integranteAEliminar = integranteActual;
        integranteActual = integranteActual->siguiente;
        delete integranteAEliminar;
    }

    delete actual;
    --cantidadGrupos;
    return true;
}

bool ListaDeListas::eliminarIntegrante(const std::string& nombreGrupo, const std::string& nombre) {
    NodoGrupo* grupo = buscarGrupo(nombreGrupo);
    if (grupo == nullptr) {
        return false;
    }

    NodoIntegrante* actual = grupo->cabezaIntegrantes;
    NodoIntegrante* anterior = nullptr;

    while (actual != nullptr && actual->nombre != nombre) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        return false;
    }

    if (anterior == nullptr) {
        grupo->cabezaIntegrantes = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
    --grupo->cantidadIntegrantes;
    return true;
}

std::size_t ListaDeListas::obtenerCantidadGrupos() const {
    return cantidadGrupos;
}

bool ListaDeListas::estaVacia() const {
    return cabeza == nullptr;
}

void ListaDeListas::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "No hay grupos registrados.\n";
        return;
    }

    const NodoGrupo* grupoActual = cabeza;
    while (grupoActual != nullptr) {
        std::cout << "Grupo: " << grupoActual->nombre
                   << " (" << grupoActual->cantidadIntegrantes << " integrantes)\n";

        const NodoIntegrante* integranteActual = grupoActual->cabezaIntegrantes;
        if (integranteActual == nullptr) {
            std::cout << "  (sin integrantes)\n";
        }
        while (integranteActual != nullptr) {
            std::cout << "  - " << integranteActual->nombre << ", "
                      << integranteActual->edad << " anios\n";
            integranteActual = integranteActual->siguiente;
        }

        grupoActual = grupoActual->siguiente;
    }
}

void ListaDeListas::graficar() const {
    if (cabeza == nullptr) {
        std::cout << "La lista esta vacia, no hay nada que graficar.\n";
        return;
    }

    std::ofstream archivo("lista_de_listas.dot");
    archivo << "digraph ListaDeListas {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    node [shape=record, style=filled, fillcolor=\"#eaff06\"];\n";

    const NodoGrupo* grupoActual = cabeza;
    std::size_t g = 0;
    std::string idsGrupos;

    while (grupoActual != nullptr) {
        archivo << "    subgraph cluster_" << g << " {\n";
        archivo << "        label=\"" << grupoActual->nombre << "\";\n";
        archivo << "        style=filled;\n";
        archivo << "        color=\"#dddddd\";\n";

        std::string idGrupo = "grupo" + std::to_string(g);
        archivo << "        " << idGrupo << " [shape=ellipse, style=filled, fillcolor=\"#9ad0f5\", label=\""
                << grupoActual->nombre << "\"];\n";

        const NodoIntegrante* integranteActual = grupoActual->cabezaIntegrantes;
        std::size_t i = 0;
        std::string idAnterior = idGrupo;

        while (integranteActual != nullptr) {
            std::string idActual = "g" + std::to_string(g) + "n" + std::to_string(i);
            archivo << "        " << idActual << " [label=\"{" << integranteActual->nombre
                    << " | " << integranteActual->edad << " anios}\"];\n";
            archivo << "        " << idAnterior << " -> " << idActual << ";\n";

            idAnterior = idActual;
            integranteActual = integranteActual->siguiente;
            ++i;
        }

        archivo << "    }\n";

        idsGrupos += idGrupo + "; ";

        grupoActual = grupoActual->siguiente;
        ++g;
    }

    archivo << "    { rank=same; " << idsGrupos << "}\n";

    for (std::size_t j = 0; j + 1 < g; ++j) {
        archivo << "    grupo" << j << " -> grupo" << j + 1
                << " [style=dashed, color=red, constraint=false];\n";
    }

    archivo << "}\n";
    archivo.close();

    int resultado = std::system("dot -Tpng lista_de_listas.dot -o lista_de_listas.png");
    if (resultado == 0) {
        std::cout << "Grafico generado: lista_de_listas.png\n";
    } else {
        std::cout << "Error: no se pudo generar el grafico. Verifica que Graphviz este instalado.\n";
    }
}