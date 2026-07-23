#include <iostream>
#include <string>

// Una funcion agrupa instrucciones que pueden reutilizarse.
int sumar(int primer_numero, int segundo_numero) {
    return primer_numero + segundo_numero;
}

void mostrarSaludo(const std::string& nombre) {
    std::cout << "Hola, " << nombre << ". Bienvenido a C++.\n";
}

int main() {
    // Tipos de datos basicos.
    int edad = 20;
    double estatura = 1.70;
    char seccion = 'A';
    bool esta_activo = true;
    std::string nombre = "Estudiante";
    const int anio_actual = 2026;

    mostrarSaludo(nombre);

    std::cout << "Edad: " << edad << '\n';
    std::cout << "Estatura: " << estatura << '\n';
    std::cout << "Seccion: " << seccion << '\n';
    std::cout << "Anio actual: " << anio_actual << '\n';

    // Operadores aritmeticos y llamada a una funcion.
    int resultado = sumar(edad, 5);
    std::cout << "Edad mas cinco: " << resultado << '\n';

    // Una condicion permite decidir que instrucciones ejecutar.
    if (esta_activo && edad >= 18) {
        std::cout << "El estudiante esta activo y es mayor de edad.\n";
    } else {
        std::cout << "No se cumplen ambas condiciones.\n";
    }

    // Un arreglo guarda varios datos del mismo tipo con un tamano fijo.
    int calificaciones[] = {75, 85, 90};
    int suma_calificaciones = 0;

    // El ciclo for recorre cada posicion del arreglo.
    for (int calificacion : calificaciones) {
        suma_calificaciones += calificacion;
        std::cout << "Calificacion: " << calificacion << '\n';
    }

    double promedio = static_cast<double>(suma_calificaciones) / 3;
    std::cout << "Promedio: " << promedio << '\n';

    // El ciclo while repite un bloque mientras la condicion sea verdadera.
    int contador = 1;
    while (contador <= 3) {
        std::cout << "Contador: " << contador << '\n';
        ++contador;
    }

    return 0;
}
