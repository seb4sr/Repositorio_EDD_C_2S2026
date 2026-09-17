#include "TablaHash.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

void linea(char caracter = '-') {
    std::cout << std::string(65, caracter) << '\n';
}

unsigned long long extraerNumeroTipo(const std::string& tipo) {
    const std::size_t posicion = tipo.find_last_not_of("0123456789");
    return std::stoull(tipo.substr(posicion + 1));
}

std::size_t sumaAscii(const std::string& texto) {
    std::size_t suma = 0;
    for (unsigned char caracter : texto) {
        suma += caracter;
    }
    return suma;
}

void mostrarCalculosHash(const TablaHash& tabla, const std::vector<std::string>& tipos) {
    for (const std::string& tipo : tipos) {
        const unsigned long long numero = extraerNumeroTipo(tipo);
        const std::size_t indice = tabla.calcularIndice(tipo);
        std::cout << "   hash(\"" << std::left << std::setw(7) << tipo << "\") = ("
                  << numero << " - 1) % " << tabla.obtenerTamano() << " = " << indice
                  << "  -> bucket[" << indice << "]\n";
    }
}

void mostrarResultados(const TablaHash& tabla, const std::string& tipo) {
    const unsigned long long numero = extraerNumeroTipo(tipo);
    const std::size_t indice = tabla.calcularIndice(tipo);
    std::cout << "  Consultando " << tipo << " (hash=(" << numero << "-1)%"
              << tabla.obtenerTamano() << '=' << indice << ", bucket[" << indice << "]):\n";

    const std::vector<TablaHash::Profesional> resultado = tabla.buscarPorTipo(tipo);
    if (resultado.empty()) {
        std::cout << "  (sin resultados)\n\n";
        return;
    }

    std::cout << "  " << std::left << std::setw(14) << "No. Colegio"
              << std::setw(22) << "Nombre" << std::setw(12) << "Depto."
              << "Especialidad\n";
    std::cout << "  " << std::string(62, '-') << '\n';
    for (const TablaHash::Profesional& profesional : resultado) {
        std::cout << "  " << std::left << std::setw(14) << profesional.numeroColegio
                  << std::setw(22) << profesional.nombre << std::setw(12)
                  << profesional.departamento << profesional.especialidad << '\n';
    }
    std::cout << '\n';
}

}

int main() {
    const std::vector<std::string> tipos = {"TIPO-01", "TIPO-02", "TIPO-03", "TIPO-04"};

    linea('=');
    std::cout << "  DEMOSTRACION: Tabla Hash\n";
    std::cout << "  Directorio del Personal por Tipo - Hospital General San Carlos\n";
    linea('=');
    std::cout << '\n';

    linea();
    std::cout << "1. FUNCION HASH  (extraccion numerica del tipo)\n\n";
    std::cout << "   hash(clave) = (numero_extraido - 1) % size\n\n";
    std::cout << "   Con size=4 obtenemos hash perfecto (0 colisiones):\n\n";
    TablaHash tabla(4);
    mostrarCalculosHash(tabla, tipos);
    std::cout << "\n   Cada tipo cae en un bucket exclusivo. Hash perfecto.\n\n";
    std::cout << "   COMPARACION con suma-ASCII (funcion debil):\n";
    for (const std::string& tipo : tipos) {
        std::cout << "   suma_ascii(\"" << std::left << std::setw(7) << tipo << "\") = "
                  << sumaAscii(tipo) << "  -> buckets consecutivos, fragil\n";
    }
    linea();

    std::cout << "\n";
    linea();
    std::cout << "2. CREANDO TABLA HASH (size=4) E INSERTANDO PERSONAL\n";
    std::cout << "   Cada usuario se inserta por su tipo; si hay varios del\n";
    std::cout << "   mismo tipo se encadenan dentro del mismo bucket.\n";
    linea();
    std::cout << '\n';

    std::cout << "-- Medicos Generales (TIPO-01) -> bucket[0] --\n";
    tabla.insertar("TIPO-01", "COL-10245", "Ana Ramirez", "DEP-MED", "Medicina General");
    tabla.insertar("TIPO-01", "COL-10389", "Luis Perez", "DEP-MED", "Medicina Interna");
    tabla.insertar("TIPO-01", "COL-99001", "Josesito Lopez", "SIN-DEP", "Medicina Interna");
    std::cout << "\n-- Medicos Especialistas / Cirujanos (TIPO-02) -> bucket[1] --\n";
    tabla.insertar("TIPO-02", "COL-20134", "Carlos Mendoza", "DEP-CIR", "Cirugia General");
    tabla.insertar("TIPO-02", "COL-20567", "Marta Estrada", "DEP-CIR", "Cirugia Cardiaca");
    std::cout << "\n-- Enfermeros/as (TIPO-03) -> bucket[2] --\n";
    tabla.insertar("TIPO-03", "COL-30101", "Lucia Flores", "DEP-MED", "Enfermeria General");
    tabla.insertar("TIPO-03", "COL-30412", "Rosa Mendez", "DEP-FAR", "Farmacologia");
    tabla.insertar("TIPO-03", "COL-30888", "Juan Castillo", "DEP-CIR", "Enfermeria Quirurgica");
    std::cout << "\n-- Tecnicos de Laboratorio (TIPO-04) -> bucket[3] --\n";
    tabla.insertar("TIPO-04", "COL-40210", "Pedro Alvarado", "DEP-LAB", "Bioquimica Clinica");
    std::cout << "\n>> Intentando insertar duplicado:\n";
    tabla.insertar("TIPO-01", "COL-10245", "Otro Nombre", "DEP-MED", "Medicina General");

    std::cout << "\n";
    linea();
    std::cout << "3. ESTADO ACTUAL DE LA TABLA HASH\n";
    linea();
    std::cout << '\n';
    tabla.imprimirEstado();

    std::cout << "\n";
    linea();
    std::cout << "4. BUSQUEDA POR TIPO\n\n";
    std::cout << "   El administrador selecciona TIPO-03 (Enfermeros).\n";
    std::cout << "   La funcion hash va directo al bucket y luego recorre su cadena.\n";
    linea();
    std::cout << "\n";
    mostrarResultados(tabla, "TIPO-01");
    mostrarResultados(tabla, "TIPO-03");

    linea();
    std::cout << "5. DEMOSTRACION DE COLISION (tabla con size=3)\n\n";
    TablaHash tablaColision(3);
    mostrarCalculosHash(tablaColision, tipos);
    std::cout << "\n   TIPO-01 y TIPO-04 apuntan al mismo bucket. El encadenamiento los une en lista.\n";
    linea();
    std::cout << '\n';
    tablaColision.insertar("TIPO-01", "COL-10245", "Ana Ramirez", "DEP-MED", "Medicina General");
    tablaColision.insertar("TIPO-02", "COL-20134", "Carlos Mendoza", "DEP-CIR", "Cirugia General");
    tablaColision.insertar("TIPO-03", "COL-30101", "Lucia Flores", "DEP-MED", "Enfermeria General");
    std::cout << "\n>> Insertar TIPO-04 - debe colisionar con TIPO-01 en bucket[0]:\n";
    tablaColision.insertar("TIPO-04", "COL-40210", "Pedro Alvarado", "DEP-LAB", "Bioquimica Clinica");
    std::cout << "\nEstado de la tabla con colision:\n\n";
    tablaColision.imprimirEstado();

    std::cout << "\n";
    linea();
    std::cout << "6. ELIMINAR USUARIO DE LA TABLA PRINCIPAL\n";
    linea();
    std::cout << "\n>> Eliminar COL-99001 (Josesito Lopez, TIPO-01):\n";
    tabla.eliminar("TIPO-01", "COL-99001");
    std::cout << "\n>> Intentar eliminar un colegio que no existe:\n";
    tabla.eliminar("TIPO-02", "COL-99999");
    std::cout << "\nTotal de profesionales tras eliminacion: " << tabla.obtenerTotal() << '\n';

    std::cout << "\n";
    linea();
    std::cout << "7. ESTADISTICAS FINALES - Tabla principal (size=4)\n";
    linea();
    std::cout << "\n  Tamano tabla    : " << tabla.obtenerTamano() << '\n';
    std::cout << "  Total elementos : " << tabla.obtenerTotal() << '\n';
    std::cout << "  Colisiones      : " << tabla.obtenerColisiones() << '\n';
    std::cout << "  Factor de carga : " << std::fixed << std::setprecision(2)
              << tabla.obtenerFactorCarga() << "\n\n";
    std::cout << "  NOTA: Factor de carga > 0.7 es senal de redimensionar.\n";
    std::cout << "        Este factor indica que tan 'llena' esta la tabla.\n";

    std::cout << "\n";
    linea();
    std::cout << "8. GENERANDO REPORTES CON GRAPHVIZ\n";
    linea();
    std::cout << '\n';
    tabla.graficar("tabla_hash_principal");
    tablaColision.graficar("tabla_hash_colision");

    std::cout << '\n';
    linea('=');
    std::cout << "  FIN DE LA DEMOSTRACION\n";
    linea('=');
    return 0;
}
