# Repositorio_EDD_C_2S2026

Proyecto base para aprender C++ y desarrollar ejercicios de Estructuras de Datos.

## Herramientas utilizadas

### C++

C++ es el lenguaje de programación que utilizaremos. Los archivos de código fuente
usan la extensión `.cpp`.

Este proyecto utiliza el estándar C++20, una versión moderna del lenguaje.

### Compilador MSVC

El compilador traduce el código escrito en C++ a un archivo ejecutable que Windows
puede correr. En este proyecto se instaló MSVC mediante Visual Studio Build Tools.

### CMake

CMake administra la configuración y compilación del proyecto. Lee el archivo
`CMakeLists.txt`, detecta el compilador disponible y genera los archivos necesarios
para construir el programa.

### Terminal

La terminal permite ejecutar comandos sin usar una interfaz gráfica. Podemos usar
la terminal integrada de VS Code con PowerShell o Símbolo del sistema (`cmd`).

## Instalación realizada en Windows

Se utilizó `winget`, el administrador de paquetes de Windows, para instalar las
herramientas.

Instalación de CMake:

```cmd
winget install --id Kitware.CMake
```

Instalación de Visual Studio Build Tools, que incluye el compilador MSVC:

```cmd
winget install --id Microsoft.VisualStudio.2022.BuildTools --override "--wait --passive --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```

La opción `Microsoft.VisualStudio.Workload.VCTools` solicita específicamente las
herramientas necesarias para compilar C++.

Después de instalar las herramientas es necesario cerrar todas las ventanas de
VS Code y abrirlo nuevamente. Esto permite que VS Code cargue la variable `PATH`
actualizada de Windows.

Para comprobar la instalación:

```cmd
cmake --version
```

Si CMake está instalado pero la terminal todavía no lo reconoce, puede agregarse
temporalmente al `PATH` de la terminal actual:

```cmd
set "PATH=C:\Program Files\CMake\bin;%PATH%"
```



## Configuración de CMake

El archivo `CMakeLists.txt` es la receta de construcción del proyecto. CMake lo lee
de arriba hacia abajo para saber qué versión necesita, qué lenguaje usamos, cómo
debe configurarse el compilador y qué archivos forman el programa.

El contenido completo que escribimos es:

```cmake
cmake_minimum_required(VERSION 3.20)

project(Repositorio_EDD_C_2S2026 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Repositorio_EDD_C_2S2026
    src/main.cpp
)
```

### Sintaxis básica de CMake

Cada instrucción de CMake tiene un nombre seguido de paréntesis:

```cmake
comando(argumento1 argumento2)
```

- El comando indica la acción que CMake debe realizar.
- Los argumentos proporcionan los datos necesarios para esa acción.
- Los argumentos se separan con espacios o saltos de línea, no con comas.
- Los paréntesis indican dónde comienza y termina la instrucción.
- Una línea vacía solo ayuda a organizar el archivo y no cambia su funcionamiento.
- Los comentarios comienzan con `#` y CMake no los ejecuta.

Por ejemplo:

```cmake
# Este es un comentario
set(CMAKE_CXX_STANDARD 20)
```

### Versión mínima de CMake

```cmake
cmake_minimum_required(VERSION 3.20)
```

Esta debe ser una de las primeras instrucciones del archivo.

- `cmake_minimum_required` es el comando.
- `VERSION` es una palabra clave que indica que el siguiente valor es una versión.
- `3.20` es la versión mínima aceptada.

Si se intenta configurar el proyecto con una versión anterior a CMake 3.20, CMake
detendrá el proceso y mostrará un error. También usa esta información para aplicar
el comportamiento correcto y compatible con esa versión.

Esta instrucción todavía no compila el programa; solo establece el requisito de
CMake para poder procesar el resto del archivo.

### Definición del proyecto

```cmake
project(Repositorio_EDD_C_2S2026 LANGUAGES CXX)
```

Esta instrucción crea y configura el proyecto.

- `project` es el comando.
- `Repositorio_EDD_C_2S2026` es el nombre que asignamos al proyecto.
- `LANGUAGES` indica que a continuación se listarán los lenguajes utilizados.
- `CXX` es el nombre que CMake usa para representar C++.

Al procesar esta línea, CMake busca un compilador de C++ instalado. En nuestra
máquina encuentra MSVC, incluido en Visual Studio Build Tools. CMake también crea
variables internas con información del proyecto y del compilador detectado.

Si no hubiera un compilador de C++ disponible, la configuración fallaría aquí y
CMake mostraría que no puede encontrar un compilador `CXX`.

El nombre escrito en `project` identifica al proyecto completo. Más adelante,
`add_executable` define un programa específico que pertenece a ese proyecto.

### Configuración del estándar C++

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

El comando `set` asigna un valor a una variable de CMake. Su forma general es:

```cmake
set(NOMBRE_DE_VARIABLE valor)
```

Las tres variables que usamos controlan la versión y el comportamiento del
lenguaje C++.

#### `CMAKE_CXX_STANDARD`

```cmake
set(CMAKE_CXX_STANDARD 20)
```

- `CMAKE_CXX_STANDARD` es una variable especial reconocida por CMake.
- `20` solicita el estándar C++20.

Los estándares de C++ definen qué características del lenguaje están disponibles.
Al elegir C++20 podemos utilizar sus funciones modernas de forma consistente.
CMake convierte esta configuración en la opción apropiada para el compilador; en
nuestro caso, configura MSVC para compilar con C++20.

#### `CMAKE_CXX_STANDARD_REQUIRED`

```cmake
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

- `ON` significa verdadero o activado en CMake.
- Esta opción obliga al compilador a usar C++20.

Sin esta opción, CMake podría intentar usar un estándar anterior si el compilador
no admite C++20. Con `ON`, la configuración falla y muestra un error en lugar de
compilar el proyecto con una versión distinta a la solicitada.

#### `CMAKE_CXX_EXTENSIONS`

```cmake
set(CMAKE_CXX_EXTENSIONS OFF)
```

- `OFF` significa falso o desactivado.
- Desactiva, cuando el compilador lo permite, extensiones particulares que no
  forman parte del estándar oficial de C++.

Esto ayuda a escribir código más portable. Un programa portable tiene menos
dependencia de un compilador específico y puede trasladarse con mayor facilidad a
otro sistema que utilice GCC, Clang o MSVC.

### Creación del ejecutable

```cmake
add_executable(Repositorio_EDD_C_2S2026
    src/main.cpp
)
```

`add_executable` crea un objetivo o *target* de compilación. Un objetivo es algo que
CMake debe construir; en este caso es un programa ejecutable.

- `Repositorio_EDD_C_2S2026` es el nombre del objetivo y del ejecutable resultante.
- `src/main.cpp` es el archivo de código fuente que se debe compilar.
- La ruta es relativa a la carpeta donde está `CMakeLists.txt`.

La instrucción ocupa varias líneas para facilitar su lectura. Sería válido escribir
todo en una sola línea:

```cmake
add_executable(Repositorio_EDD_C_2S2026 src/main.cpp)
```

Cuando ejecutamos `cmake --build build`, CMake ordena a MSVC que compile
`src/main.cpp`. El compilador genera código objeto y después el enlazador lo combina
con las bibliotecas necesarias para producir
`Repositorio_EDD_C_2S2026.exe`.

En nuestro proyecto, Visual Studio guarda el ejecutable de la configuración Debug
en:

```text
build/Debug/Repositorio_EDD_C_2S2026.exe
```

### Agregar nuevos archivos al proyecto

Si después creamos los archivos `src/lista.cpp` y `src/lista.h`, el archivo con la
implementación debe agregarse al objetivo:

```cmake
add_executable(Repositorio_EDD_C_2S2026
    src/main.cpp
    src/lista.cpp
    src/lista.h
)
```

Los archivos `.cpp` contienen código que el compilador transforma por separado. Los
archivos `.h` contienen normalmente declaraciones que se incluyen desde los `.cpp`.
Agregar el `.h` a `add_executable` es útil para que aparezca organizado en algunas
herramientas, aunque el compilador procesa principalmente los `.cpp`.

Después de modificar `CMakeLists.txt`, se puede ejecutar nuevamente:

```cmd
cmake -S . -B build
cmake --build build
```

El primer comando actualiza la configuración y el segundo vuelve a construir el
ejecutable con todos los archivos indicados.

### Qué ocurre durante el proceso completo

Al ejecutar `cmake -S . -B build`, CMake:

1. Busca y lee `CMakeLists.txt`.
2. Verifica que su versión sea al menos 3.20.
3. Detecta el compilador MSVC para el lenguaje C++.
4. Configura el uso obligatorio de C++20.
5. Registra el objetivo `Repositorio_EDD_C_2S2026` y sus archivos fuente.
6. Genera dentro de `build` los archivos que Visual Studio necesita para compilar.

Al ejecutar `cmake --build build`, CMake usa esos archivos generados para pedirle al
compilador que cree el programa. CMake coordina el proceso, pero MSVC es quien
traduce realmente el código C++ a instrucciones ejecutables por Windows.

## Compilar el proyecto

Los siguientes comandos deben ejecutarse desde la carpeta principal del proyecto.

### 1. Configurar

```cmd
cmake -S . -B build
```

- `cmake`: ejecuta la herramienta CMake.
- `-S .`: indica que el código y `CMakeLists.txt` están en la carpeta actual.
- `-B build`: indica que los archivos generados se guardarán en `build`.

### 2. Compilar

```cmd
cmake --build build
```

CMake usa el compilador MSVC para transformar `src/main.cpp` en un programa
ejecutable.

### 3. Ejecutar

```cmd
.\build\Debug\Repositorio_EDD_C_2S2026.exe
```

La ruta comienza con `.\` porque el ejecutable se busca a partir de la carpeta
actual. `Debug` es la configuración de compilación que Visual Studio utiliza por
defecto.

## Fundamentos de C++ puestos en práctica

El archivo `src/main.cpp` comienza con:

```cpp
#include <iostream>
#include <string>
```

`#include` permite utilizar herramientas de la biblioteca estándar de C++.
`iostream` proporciona la salida en consola y `string` permite trabajar con texto.

```cpp
int main() {
```

La función `main` es el punto de entrada del programa. La ejecución comienza aquí.
El tipo `int` indica que la función devuelve un número entero al sistema operativo.

```cpp
const std::string nombre_proyecto = "Repositorio_EDD_C_2S2026";
```

- `std::string` es un tipo de dato utilizado para guardar texto.
- `nombre_proyecto` es el nombre de la variable.
- `const` indica que su valor no puede cambiar después de ser asignado.
- `std::` indica que `string` pertenece a la biblioteca estándar de C++.

```cpp
std::cout << "Bienvenido a " << nombre_proyecto << " en C++." << std::endl;
```

- `std::cout` envía información a la consola.
- `<<` agrega cada dato a la salida.
- El texto entre comillas es una cadena de caracteres.
- `std::endl` termina la línea.
- El punto y coma `;` marca el final de una instrucción.

```cpp
return 0;
```

Finaliza el programa. El valor `0` indica que terminó correctamente.

Las llaves `{` y `}` delimitan el bloque de instrucciones que pertenece a la
función `main`.

## Flujo de trabajo

Cada vez que se modifique el código:

```cmd
cmake --build build
.\build\Debug\Repositorio_EDD_C_2S2026.exe
```

Solo es necesario repetir `cmake -S . -B build` cuando se configura el proyecto
por primera vez o cuando cambia la configuración de `CMakeLists.txt`.

Los ejercicios y estructuras de datos se organizarán por semana dentro del
repositorio, por ejemplo en `Semana1/`.

## Fundamentos básicos de programación en C++

Aprender C++ no consiste solamente en memorizar su sintaxis. Es necesario entender
cómo se representa la información, cómo se organiza un programa y cómo se administra
la memoria. Los siguientes temas forman la base que se debe dominar.

### Proceso de compilación

Un programa de C++ pasa principalmente por estas etapas:

1. El preprocesador procesa instrucciones como `#include` y `#define`.
2. El compilador traduce cada archivo `.cpp` a código objeto.
3. El enlazador une los archivos objeto y las bibliotecas utilizadas.
4. El resultado final es un archivo ejecutable.

Es importante comprender la diferencia entre errores de compilación, errores de
enlazado y errores que aparecen durante la ejecución.

### Variables y tipos de datos

Una variable reserva un espacio para almacenar un valor. Algunos tipos básicos son:

```cpp
int cantidad = 10;           // Número entero.
double precio = 15.75;       // Número con decimales.
char grupo = 'A';            // Un carácter.
bool disponible = true;      // Valor verdadero o falso.
std::string nombre = "Ana"; // Texto.
```

Se debe estudiar:

- Tamaño y rango de cada tipo.
- Diferencia entre tipos con signo y sin signo.
- Conversiones implícitas y explícitas.
- Pérdida de precisión y desbordamiento.
- Inferencia de tipos con `auto`.
- Uso de `const` para valores que no deben cambiar.

### Operadores

Los operadores permiten realizar cálculos y comparaciones:

```cpp
int suma = 5 + 3;
bool es_mayor = suma > 6;
bool condicion = es_mayor && suma != 10;
```

Se deben conocer los operadores aritméticos, relacionales, lógicos, de asignación e
incremento. También se debe estudiar su precedencia para saber en qué orden se
evalúan las expresiones.

### Condiciones

Las condiciones permiten que el programa tome decisiones:

```cpp
if (edad >= 18) {
    std::cout << "Mayor de edad\n";
} else {
    std::cout << "Menor de edad\n";
}
```

También se debe aprender `else if`, `switch` y el operador ternario
`condicion ? valor1 : valor2`. Conviene practicar condiciones combinadas sin crear
bloques difíciles de leer.

### Ciclos

Los ciclos repiten instrucciones:

```cpp
for (int i = 0; i < 5; ++i) {
    std::cout << i << '\n';
}
```

Se debe comprender cuándo utilizar `for`, `while`, `do while` y el `for` basado en
rango. También hay que aprender el propósito de `break` y `continue`, y evitar ciclos
infinitos o accesos fuera de los límites de un arreglo.

### Funciones

Las funciones dividen un problema grande en operaciones pequeñas y reutilizables:

```cpp
int sumar(int a, int b) {
    return a + b;
}
```

Es necesario estudiar:

- Parámetros y valores de retorno.
- Paso por valor, referencia y referencia constante.
- Alcance y tiempo de vida de las variables.
- Sobrecarga de funciones.
- Parámetros predeterminados.
- Funciones recursivas.

Una función debería tener una responsabilidad clara y un nombre que explique su
propósito.

### Arreglos, cadenas y contenedores

Un arreglo guarda una cantidad fija de elementos del mismo tipo:

```cpp
int numeros[3] = {10, 20, 30};
```

Después de comprender los arreglos se debe estudiar:

- `std::array` para arreglos de tamaño fijo.
- `std::vector` para colecciones de tamaño dinámico.
- `std::string` para cadenas de caracteres.
- Acceso mediante índices e iteración.
- Diferencia entre tamaño y capacidad.
- Riesgos de acceder a una posición que no existe.

Aunque en los ejercicios de estructuras de datos se implementen listas manualmente,
también es importante aprender los contenedores de la biblioteca estándar. En
programas reales normalmente se prefieren porque ya están probados y administran sus
recursos de forma segura.

### Punteros y referencias

Un puntero almacena la dirección de memoria de otro dato:

```cpp
int numero = 10;
int* puntero = &numero;
std::cout << *puntero;
```

- `&numero` obtiene la dirección de la variable.
- `int*` declara un puntero hacia un entero.
- `*puntero` accede al valor almacenado en esa dirección.
- `nullptr` representa un puntero que no apunta a un objeto válido.

Las referencias proporcionan otro nombre para un objeto existente:

```cpp
int& referencia = numero;
```

Este tema se debe estudiar con profundidad porque es la base de las listas enlazadas,
árboles, memoria dinámica y paso eficiente de argumentos.

### Memoria automática y dinámica

Las variables locales se destruyen automáticamente al terminar su bloque. La memoria
reservada manualmente con `new` debe liberarse con `delete`:

```cpp
int* numero = new int(25);
delete numero;
numero = nullptr;
```

Se debe aprender a reconocer:

- Fugas de memoria.
- Punteros colgantes.
- Doble liberación de memoria.
- Acceso a memoria no inicializada.
- Diferencia conceptual entre pila y montón.

En C++ moderno se evita utilizar `new` y `delete` directamente cuando no son
necesarios. Para administrar propiedad dinámica se estudian `std::unique_ptr` y
`std::shared_ptr`.

### Estructuras, clases y objetos

Una clase agrupa datos y operaciones relacionadas:

```cpp
class Persona {
public:
    void mostrarNombre() const;

private:
    std::string nombre;
};
```

Se debe comprender:

- Diferencia entre `class` y `struct`.
- Encapsulamiento con `public`, `private` y `protected`.
- Constructores y destructores.
- Métodos y atributos.
- Uso de `this`.
- Métodos constantes.
- Composición entre objetos.
- Separación entre archivos `.h` y `.cpp`.

### Tipos de datos abstractos

Un tipo de dato abstracto, o TDA, define qué operaciones ofrece una estructura sin
obligar al usuario a conocer su implementación interna. Nuestra lista enlazada expone
operaciones como `insertar`, `eliminar`, `obtenerTamano` e `imprimir`, pero mantiene
los nodos y punteros como datos privados.

Para dominar este concepto se deben implementar y comparar:

- Lista simplemente enlazada.
- Lista doblemente enlazada.
- Pila.
- Cola.
- Árbol binario y árbol binario de búsqueda.
- Tabla hash.
- Grafo.

También se debe entender qué invariantes debe conservar cada estructura después de
una operación.

### Algoritmos y complejidad

No basta con obtener un resultado correcto; también importa cuántos recursos utiliza
el programa. La notación Big O describe cómo crece el tiempo o la memoria de un
algoritmo al aumentar la entrada.

Ejemplos comunes:

- `O(1)`: tiempo constante.
- `O(log n)`: tiempo logarítmico.
- `O(n)`: tiempo lineal.
- `O(n log n)`: común en algoritmos de ordenamiento eficientes.
- `O(n²)`: normalmente aparece al usar dos recorridos anidados.

Se recomienda analizar la complejidad de inserción, búsqueda y eliminación en cada
estructura de datos.

### Errores, pruebas y depuración

Un programador debe aprender a localizar problemas y no depender únicamente de que
el programa compile. Se debe practicar:

- Lectura completa de los mensajes del compilador.
- Uso de puntos de interrupción y ejecución paso a paso.
- Inspección de variables y punteros en el depurador.
- Pruebas de casos normales, límites y entradas inválidas.
- Uso de `assert` para comprobar condiciones internas.
- Pruebas unitarias automatizadas.
- Advertencias del compilador y analizadores estáticos.

Por ejemplo, una lista debe probarse vacía, con un elemento, con varios elementos,
eliminando la cabeza, eliminando el último nodo y buscando un valor inexistente.

## Temas para alcanzar un nivel intermedio

Después de dominar los fundamentos, se recomienda profundizar en los siguientes
temas.

### Biblioteca estándar de C++

La biblioteca estándar evita implementar nuevamente herramientas de uso común. Se
deben conocer:

- Contenedores: `vector`, `array`, `deque`, `list`, `map`, `set` y sus variantes.
- Algoritmos: `sort`, `find`, `count`, `transform` y `remove_if`.
- Iteradores para recorrer contenedores.
- Funciones lambda.
- Utilidades como `pair`, `tuple` y `optional`.
- Manejo de tiempo con `chrono`.
- Entrada y salida de archivos con `fstream`.

También se debe aprender a elegir el contenedor adecuado según las operaciones que
el programa realiza con mayor frecuencia.

### Programación orientada a objetos

Además del encapsulamiento básico, se debe estudiar:

- Herencia y composición.
- Funciones virtuales y polimorfismo.
- Clases abstractas e interfaces.
- Destructores virtuales.
- Sobrescritura con `override`.
- Problemas de utilizar herencia innecesariamente.

En general, se debe preferir composición cuando un objeto contiene o utiliza otro, y
reservar la herencia para relaciones donde un tipo realmente representa una
especialización de otro.

### Administración de recursos y RAII

RAII significa que un recurso se adquiere durante la construcción de un objeto y se
libera automáticamente en su destrucción. Esta idea se aplica a memoria, archivos,
bloqueos y conexiones.

Se debe estudiar:

- Regla de cero.
- Regla de tres.
- Regla de cinco.
- Constructor y operador de copia.
- Constructor y operador de movimiento.
- `std::unique_ptr`, `std::shared_ptr` y `std::weak_ptr`.
- Seguridad ante excepciones.

La copia profunda de una lista enlazada es un buen ejercicio para aprender la regla
de tres. Implementar movimiento es el siguiente paso para comprender la regla de
cinco.

### Plantillas

Las plantillas permiten escribir código que trabaja con diferentes tipos:

```cpp
template <typename T>
T mayor(T a, T b) {
    return a > b ? a : b;
}
```

Después se puede convertir la lista de enteros en una lista genérica:

```cpp
ListaEnlazadaSimple<int> numeros;
ListaEnlazadaSimple<std::string> nombres;
```

Se deben estudiar plantillas de funciones, plantillas de clases, especialización y
restricciones con conceptos de C++20.

### Manejo de errores

Se deben conocer diferentes formas de comunicar errores:

- Valores de retorno.
- Excepciones con `try`, `throw` y `catch`.
- `std::optional` cuando un resultado puede no existir.
- `std::expected` en versiones recientes del estándar.

La estrategia depende del tipo de error. No todos los errores deben convertirse en
excepciones.

## Temas para alcanzar un nivel avanzado

El nivel avanzado requiere entender tanto la abstracción de alto nivel como el
funcionamiento interno del lenguaje.

### Modelo de objetos y semántica del lenguaje

Se recomienda estudiar con profundidad:

- Tiempo de vida de los objetos.
- Categorías de valores: `lvalue`, `rvalue` y referencias universales.
- Semántica de movimiento y reenvío perfecto.
- Sobrecarga de operadores.
- Conversión de tipos y constructores de conversión.
- Alineación, representación y distribución de memoria.
- Comportamiento indefinido.
- Reglas de `const` y constancia lógica.

### Plantillas avanzadas y programación genérica

Se deben estudiar:

- Deducción de tipos.
- Plantillas variádicas.
- Expresiones `constexpr` y evaluación en compilación.
- Conceptos y restricciones de C++20.
- Metaprogramación.
- Diseño de algoritmos genéricos mediante iteradores y rangos.

### Concurrencia

Para desarrollar programas que realizan varias tareas simultáneamente se debe
aprender:

- Hilos con `std::thread` y `std::jthread`.
- Exclusión mutua con `std::mutex`.
- Bloqueos administrados mediante RAII.
- Variables de condición.
- Operaciones atómicas.
- Condiciones de carrera y bloqueos mutuos.
- Modelo de memoria de C++.

La concurrencia debe estudiarse después de dominar el tiempo de vida, la propiedad y
la administración de recursos.

### Diseño y arquitectura

Un nivel avanzado también requiere escribir software mantenible:

- Principios de responsabilidad única y separación de responsabilidades.
- Interfaces pequeñas y claras.
- Bajo acoplamiento y alta cohesión.
- Manejo explícito de propiedad y tiempo de vida.
- Patrones de diseño utilizados con criterio.
- Organización en bibliotecas y módulos.
- Compatibilidad entre plataformas.

### Herramientas profesionales

Además del lenguaje, se debe aprender a utilizar:

- Git para control de versiones.
- CMake para proyectos con varios objetivos y bibliotecas.
- Depuradores como el de Visual Studio o GDB.
- Sanitizadores de memoria y comportamiento indefinido.
- Analizadores estáticos como `clang-tidy`.
- Formateadores como `clang-format`.
- Sistemas de pruebas como GoogleTest o Catch2.
- Documentación y revisión de código.
- Integración continua para compilar y probar automáticamente.

## Ruta práctica recomendada

Una posible ruta de aprendizaje para este repositorio es:

1. Programas pequeños con variables, operadores, condiciones y ciclos.
2. Funciones, arreglos, cadenas y separación en archivos `.h` y `.cpp`.
3. Punteros, referencias y memoria dinámica.
4. Lista simplemente enlazada con inserción, búsqueda y eliminación.
5. Copia profunda y regla de tres para la lista.
6. Lista doblemente enlazada, pila y cola.
7. Recursividad, árboles y recorridos.
8. Algoritmos de búsqueda y ordenamiento con análisis Big O.
9. Plantillas para convertir las estructuras en tipos genéricos.
10. Uso equivalente de contenedores y algoritmos de la biblioteca estándar.
11. Pruebas unitarias y detección de errores de memoria.
12. Proyecto completo con CMake, Git y documentación.

Para cada tema se recomienda seguir este proceso:

1. Comprender el problema y dibujar la estructura o el flujo.
2. Implementar una primera versión sencilla.
3. Probar casos normales y casos límite.
4. Analizar el tiempo y la memoria utilizados.
5. Comparar la implementación manual con la biblioteca estándar.
6. Explicar el código sin leerlo; si no se puede explicar, todavía falta práctica.
7. Refactorizar el código para mejorar claridad y seguridad.

Llegar a un nivel avanzado no depende únicamente de cubrir una lista de temas. Es
necesario construir proyectos, encontrar errores, leer código de otras personas y
aprender a justificar por qué se elige una solución sobre otra.
