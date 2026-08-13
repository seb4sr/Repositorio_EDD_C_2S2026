#ifndef LISTA_DE_LISTAS_H
#define LISTA_DE_LISTAS_H

#include <cstddef>
#include <string>

class ListaDeListas {
public:
    ListaDeListas();
    ~ListaDeListas();

    ListaDeListas(const ListaDeListas&) = delete;
    ListaDeListas& operator=(const ListaDeListas&) = delete;

    bool insertarGrupo(const std::string& nombreGrupo);
    bool insertarIntegrante(const std::string& nombreGrupo, const std::string& nombre, int edad);
    bool eliminarGrupo(const std::string& nombreGrupo);
    bool eliminarIntegrante(const std::string& nombreGrupo, const std::string& nombre);
    [[nodiscard]] std::size_t obtenerCantidadGrupos() const;
    [[nodiscard]] bool estaVacia() const;
    void mostrar() const;
    void graficar() const;

private:
    struct NodoIntegrante {
        std::string nombre;
        int edad;
        NodoIntegrante* siguiente;
    };

    struct NodoGrupo {
        std::string nombre;
        NodoIntegrante* cabezaIntegrantes;
        std::size_t cantidadIntegrantes;
        NodoGrupo* siguiente;
    };

    NodoGrupo* buscarGrupo(const std::string& nombreGrupo) const;

    NodoGrupo* cabeza;
    std::size_t cantidadGrupos;
};

#endif