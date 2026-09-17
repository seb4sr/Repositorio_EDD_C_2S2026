#include "TablaHash.h"

#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

TablaHash::TablaHash(std::size_t tamano)
    : tamano(tamano), buckets(tamano), total(0), colisiones(0) {
    if (tamano == 0) {
        throw std::invalid_argument("El tamano de la tabla debe ser mayor que cero.");
    }
}

std::size_t TablaHash::calcularIndice(const std::string& clave) const { // esto es sinomino de que es mi hash
    std::size_t inicioNumero = clave.size();
    while (inicioNumero > 0 && std::isdigit(static_cast<unsigned char>(clave[inicioNumero - 1]))) {
        --inicioNumero;
    }

    if (inicioNumero < clave.size()) {
        const unsigned long long numero = std::stoull(clave.substr(inicioNumero));
        if (numero > 0) {
            return static_cast<std::size_t>((numero - 1) % tamano);
        }
    }

    std::size_t suma = 0;
    for (unsigned char caracter : clave) {
        suma += caracter;
    }
    return suma % tamano;
}

bool TablaHash::insertar(const std::string& tipo, const std::string& numeroColegio,
                         const std::string& nombre, const std::string& departamento,
                         const std::string& especialidad) {
    const std::size_t indice = calcularIndice(tipo);
    std::vector<Profesional>& bucket = buckets[indice];

    for (const Profesional& profesional : bucket) {
        if (profesional.numeroColegio == numeroColegio) {
            std::cout << "  [AVISO] " << numeroColegio
                      << " ya existe en la tabla. No se inserto duplicado.\n";
            return false;
        }
    }

    if (!bucket.empty() && bucket.front().tipo != tipo) {
        ++colisiones;
        std::cout << "  [COLISION] '" << tipo << "' colisiona con '"
                  << bucket.front().tipo << "' en bucket[" << indice
                  << "] -> se encadena\n";
    }

    bucket.push_back({tipo, numeroColegio, nombre, departamento, especialidad});
    ++total;
    std::cout << "  [INSERT] " << std::left << std::setw(12) << numeroColegio
              << "  bucket[" << indice << "]  tipo: " << tipo << '\n';
    return true;
}

std::vector<TablaHash::Profesional> TablaHash::buscarPorTipo(const std::string& tipo) const {
    const std::vector<Profesional>& bucket = buckets[calcularIndice(tipo)];
    std::vector<Profesional> resultado;

    for (const Profesional& profesional : bucket) {
        if (profesional.tipo == tipo) {
            resultado.push_back(profesional);
        }
    }

    return resultado;
}

bool TablaHash::eliminar(const std::string& tipo, const std::string& numeroColegio) {
    const std::size_t indice = calcularIndice(tipo);
    std::vector<Profesional>& bucket = buckets[indice];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->tipo == tipo && it->numeroColegio == numeroColegio) {
            bucket.erase(it);
            --total;
            std::cout << "  [DELETE] " << numeroColegio << " eliminado del bucket["
                      << indice << "]\n";
            return true;
        }
    }

    std::cout << "  [AVISO] " << numeroColegio << " no encontrado en tipo '"
              << tipo << "'.\n";
    return false;
}

double TablaHash::obtenerFactorCarga() const {
    return static_cast<double>(total) / static_cast<double>(tamano);
}

std::size_t TablaHash::obtenerColisiones() const {
    return colisiones;
}

std::size_t TablaHash::obtenerTotal() const {
    return total;
}

std::size_t TablaHash::obtenerTamano() const {
    return tamano;
}

const std::vector<std::vector<TablaHash::Profesional>>& TablaHash::obtenerBuckets() const {
    return buckets;
}

void TablaHash::imprimirEstado() const {
    std::cout << "  Tamano tabla    : " << tamano << " buckets\n";
    std::cout << "  Total elementos : " << total << '\n';
    std::cout << "  Colisiones      : " << colisiones << '\n';
    std::cout << "  Factor de carga : " << std::fixed << std::setprecision(2)
              << obtenerFactorCarga() << "  (" << std::setprecision(0)
              << obtenerFactorCarga() * 100.0 << "% ocupado)\n\n";

    std::size_t ocupados = 0;
    for (std::size_t i = 0; i < tamano; ++i) {
        const std::vector<Profesional>& bucket = buckets[i];
        if (bucket.empty()) {
            std::cout << "  Bucket[" << std::setw(2) << i << "] (vacio)\n";
            continue;
        }

        ++ocupados;
        std::cout << "  Bucket[" << std::setw(2) << i << "] (" << bucket.size()
                  << " entrada" << (bucket.size() == 1 ? "" : "s") << "): ";
        for (const Profesional& profesional : bucket) {
            std::cout << "[" << profesional.tipo << " | " << profesional.numeroColegio
                      << " | " << profesional.nombre << "] -> ";
        }
        std::cout << "NULL\n";
    }

    std::cout << "\n  Slots ocupados  : " << ocupados << " / " << tamano << '\n';
}

std::string TablaHash::escaparDot(const std::string& texto) {
    std::string resultado;
    for (char caracter : texto) {
        if (caracter == '\\' || caracter == '"') {
            resultado += '\\';
        }
        resultado += caracter;
    }
    return resultado;
}

void TablaHash::graficar(const std::string& nombreBase) const {
    std::filesystem::create_directories("reportes");
    const std::string rutaDot = "reportes/" + nombreBase + ".dot";
    const std::string rutaPng = "reportes/" + nombreBase + ".png";
    std::ofstream archivo(rutaDot);

    if (!archivo) {
        std::cout << "  Error al crear " << rutaDot << ".\n";
        return;
    }

    archivo << "digraph TablaHash {\n";
    archivo << "    rankdir=LR;\n";
    archivo << "    splines=ortho;\n";
    archivo << "    node [shape=record, style=filled, fontname=\"Courier\", fontsize=10];\n";
    archivo << "    edge [arrowhead=vee, fontname=\"Arial\", fontsize=9];\n\n";
    archivo << "    titulo [label=\"Tabla Hash\\nSize=" << tamano << " | Total=" << total
            << " | Colisiones=" << colisiones << " | FC=" << std::fixed << std::setprecision(2)
            << obtenerFactorCarga() << "\", shape=box, fillcolor=\"#EAECEE\", fontsize=12];\n\n";

    for (std::size_t i = 0; i < tamano; ++i) {
        const std::vector<Profesional>& bucket = buckets[i];
        if (bucket.empty()) {
            archivo << "    bucket_" << i << " [label=\"{bucket[" << i
                    << "] | vacio}\", fillcolor=\"#F2F3F4\"];\n";
        } else {
            archivo << "    bucket_" << i << " [label=\"{bucket[" << i << "] | "
                    << escaparDot(bucket.front().tipo) << " | " << bucket.size()
                    << " nodo(s)}\", fillcolor=\"#D5D8DC\"];\n";
        }
    }

    const std::vector<std::string> colores = {"#AED6F1", "#FAD7A0", "#A9DFBF", "#F9E79F"};
    for (std::size_t i = 0; i < tamano; ++i) {
        const std::vector<Profesional>& bucket = buckets[i];
        for (std::size_t j = 0; j < bucket.size(); ++j) {
            const Profesional& profesional = bucket[j];
            const std::size_t color = calcularIndice(profesional.tipo) % colores.size();
            archivo << "    nodo_" << i << '_' << j << " [label=\"{"
                    << escaparDot(profesional.numeroColegio) << "\\n"
                    << escaparDot(profesional.nombre) << "\\n"
                    << escaparDot(profesional.departamento) << " | "
                    << escaparDot(profesional.tipo) << "}\", fillcolor=\""
                    << colores[color] << "\"];\n";
        }
        if (!bucket.empty()) {
            archivo << "    bucket_" << i << " -> nodo_" << i << "_0;\n";
            for (std::size_t j = 0; j + 1 < bucket.size(); ++j) {
                archivo << "    nodo_" << i << '_' << j << " -> nodo_" << i << '_'
                        << j + 1 << ";\n";
            }
            archivo << "    null_" << i << " [label=\"NULL\", fillcolor=\"#FADBD8\"];\n";
            archivo << "    nodo_" << i << '_' << bucket.size() - 1 << " -> null_" << i << ";\n";
        }
    }

    archivo << "}\n";
    archivo.close();

    const std::string comando = "dot -Tpng \"" + rutaDot + "\" -o \"" + rutaPng + "\"";
    if (std::system(comando.c_str()) == 0) {
        std::cout << "  Imagen generada: " << rutaPng << '\n';
    } else {
        std::cout << "  Error al generar imagen. Verifica que Graphviz este instalado.\n";
    }
}
