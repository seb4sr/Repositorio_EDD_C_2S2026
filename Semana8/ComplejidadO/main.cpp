#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

namespace {

struct ResultadoBusqueda {
    bool encontrado;
    std::size_t pasos;
};

struct ResultadoParejas {
    bool hayDuplicado;
    std::size_t comparaciones;
};

int obtenerPrimero(const std::vector<int>& datos) {
    return datos.front();
}

ResultadoBusqueda buscarLineal(const std::vector<int>& datos, int objetivo) {
    std::size_t pasos = 0;

    for (int dato : datos) {
        ++pasos;
        if (dato == objetivo) {
            return {true, pasos};
        }
    }

    return {false, pasos};
}

ResultadoBusqueda buscarBinaria(const std::vector<int>& datosOrdenados, int objetivo) {
    std::size_t inicio = 0;
    std::size_t fin = datosOrdenados.size();
    std::size_t pasos = 0;

    while (inicio < fin) {
        const std::size_t medio = inicio + (fin - inicio) / 2;
        ++pasos;

        if (datosOrdenados[medio] == objetivo) {
            return {true, pasos};
        }
        if (objetivo < datosOrdenados[medio]) {
            fin = medio;
        } else {
            inicio = medio + 1;
        }
    }

    return {false, pasos};
}

ResultadoParejas compararTodasLasParejas(const std::vector<int>& codigos) {
    std::size_t comparaciones = 0;
    bool hayDuplicado = false;

    for (std::size_t i = 0; i < codigos.size(); ++i) {
        for (std::size_t j = i + 1; j < codigos.size(); ++j) {
            ++comparaciones;
            if (codigos[i] == codigos[j]) {
                hayDuplicado = true;
            }
        }
    }

    return {hayDuplicado, comparaciones};
}

void mezclar(std::vector<int>& datos, std::vector<int>& auxiliar,
             std::size_t inicio, std::size_t medio, std::size_t fin,
             std::size_t& comparaciones) {
    std::size_t izquierda = inicio;
    std::size_t derecha = medio;
    std::size_t destino = inicio;

    while (izquierda < medio && derecha < fin) {
        ++comparaciones;
        if (datos[izquierda] <= datos[derecha]) {
            auxiliar[destino++] = datos[izquierda++];
        } else {
            auxiliar[destino++] = datos[derecha++];
        }
    }

    while (izquierda < medio) {
        auxiliar[destino++] = datos[izquierda++];
    }
    while (derecha < fin) {
        auxiliar[destino++] = datos[derecha++];
    }

    for (std::size_t i = inicio; i < fin; ++i) {
        datos[i] = auxiliar[i];
    }
}

void ordenarMezcla(std::vector<int>& datos, std::vector<int>& auxiliar,
                   std::size_t inicio, std::size_t fin, std::size_t& comparaciones) {
    if (fin - inicio <= 1) {
        return;
    }

    const std::size_t medio = inicio + (fin - inicio) / 2;
    ordenarMezcla(datos, auxiliar, inicio, medio, comparaciones);
    ordenarMezcla(datos, auxiliar, medio, fin, comparaciones);
    mezclar(datos, auxiliar, inicio, medio, fin, comparaciones);
}

std::size_t ordenarConMergeSort(std::vector<int>& datos) {
    std::vector<int> auxiliar(datos.size());
    std::size_t comparaciones = 0;
    ordenarMezcla(datos, auxiliar, 0, datos.size(), comparaciones);
    return comparaciones;
}

std::vector<int> crearDatosDescendentes(std::size_t cantidad) {
    std::vector<int> datos;
    datos.reserve(cantidad);

    for (std::size_t valor = cantidad; valor > 0; --valor) {
        datos.push_back(static_cast<int>(valor));
    }

    return datos;
}

void mostrarLinea() {
    std::cout << "------------------------------------------------------------\n";
}

void mostrarTablaCrecimiento() {
    const std::vector<std::size_t> tamanios = {8, 16, 32};

    std::cout << "\nComparacion de crecimiento (contadores de operaciones)\n";
    std::cout << std::left << std::setw(8) << "n"
              << std::setw(12) << "O(1)"
              << std::setw(12) << "O(n)"
              << std::setw(14) << "O(log n)"
              << std::setw(14) << "O(n^2)"
              << "O(n log n)\n";

    for (std::size_t n : tamanios) {
        const std::vector<int> ordenados = crearDatosDescendentes(n);
        const ResultadoBusqueda lineal = buscarLineal(ordenados, 0);

        std::vector<int> ascendente = ordenados;
        std::reverse(ascendente.begin(), ascendente.end());
        const ResultadoBusqueda binaria = buscarBinaria(ascendente, 0);

        std::vector<int> paraOrdenar = ordenados;
        const std::size_t mezcla = ordenarConMergeSort(paraOrdenar);

        std::cout << std::left << std::setw(8) << n
                  << std::setw(12) << 1
                  << std::setw(12) << lineal.pasos
                  << std::setw(14) << binaria.pasos
                  << std::setw(14) << compararTodasLasParejas(ordenados).comparaciones
                  << mezcla << '\n';
    }
}

} // namespace

int main() {
    const std::vector<int> edadesOrdenadas = {12, 15, 18, 20, 22, 25, 30, 35};

    std::cout << "Semana 8 - Ejemplos de complejidad O\n";
    mostrarLinea();

    std::cout << "O(1): la primera edad es " << obtenerPrimero(edadesOrdenadas)
              << ". Se accede directamente por posicion.\n";

    const ResultadoBusqueda lineal = buscarLineal(edadesOrdenadas, 35);
    std::cout << "O(n): buscar 35 de forma lineal requirio " << lineal.pasos
              << " revisiones.\n";

    const ResultadoBusqueda binaria = buscarBinaria(edadesOrdenadas, 35);
    std::cout << "O(log n): buscar 35 en datos ordenados requirio " << binaria.pasos
              << " revisiones, descartando la mitad en cada paso.\n";

    const ResultadoParejas parejas = compararTodasLasParejas(edadesOrdenadas);
    std::cout << "O(n^2): revisar codigos repetidos requirio " << parejas.comparaciones
              << " comparaciones; duplicado: " << (parejas.hayDuplicado ? "si" : "no") << ".\n";

    std::vector<int> edadesDesordenadas = {35, 12, 30, 15, 25, 18, 22, 20};
    const std::size_t mezcla = ordenarConMergeSort(edadesDesordenadas);
    std::cout << "O(n log n): Merge Sort ordeno 8 edades con " << mezcla
              << " comparaciones entre elementos.\n";

    mostrarTablaCrecimiento();

    std::cout << "\nLos contadores varian segun los datos; la O expresa como crece el trabajo.\n";
    return 0;
}
