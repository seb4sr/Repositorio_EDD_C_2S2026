#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <cstddef>
#include <string>
#include <vector>

class TablaHash {
public:
    struct Profesional {
        std::string tipo;
        std::string numeroColegio;
        std::string nombre;
        std::string departamento;
        std::string especialidad;
    };

    explicit TablaHash(std::size_t tamano);

    bool insertar(const std::string& tipo, const std::string& numeroColegio,
                  const std::string& nombre, const std::string& departamento,
                  const std::string& especialidad);
    [[nodiscard]] std::vector<Profesional> buscarPorTipo(const std::string& tipo) const;
    bool eliminar(const std::string& tipo, const std::string& numeroColegio);

    [[nodiscard]] std::size_t calcularIndice(const std::string& clave) const;
    [[nodiscard]] double obtenerFactorCarga() const;
    [[nodiscard]] std::size_t obtenerColisiones() const;
    [[nodiscard]] std::size_t obtenerTotal() const;
    [[nodiscard]] std::size_t obtenerTamano() const;
    [[nodiscard]] const std::vector<std::vector<Profesional>>& obtenerBuckets() const;

    void imprimirEstado() const;
    void graficar(const std::string& nombreBase) const;

private:
    [[nodiscard]] static std::string escaparDot(const std::string& texto);

    std::size_t tamano;
    std::vector<std::vector<Profesional>> buckets;
    std::size_t total;
    std::size_t colisiones;
};

#endif
