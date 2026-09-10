# Semana 8 - Complejidad O

Ejemplos ejecutables de complejidad algorítmica con C++20. El programa no mide
tiempo: cuenta operaciones representativas para observar cómo cambia el trabajo
al aumentar `n`.

Incluye cinco casos prácticos:

- `O(1)`: acceder al primer elemento de una colección no vacía.
- `O(n)`: buscar una edad revisando los elementos en orden.
- `O(log n)`: buscar una edad con búsqueda binaria en datos ordenados.
- `O(n^2)`: comparar cada pareja posible de códigos.
- `O(n log n)`: ordenar edades mediante Merge Sort.

## Compilar y ejecutar

```cmd
cmake -S Semana8/ComplejidadO -B Semana8/ComplejidadO/build
cmake --build Semana8/ComplejidadO/build
.\Semana8\ComplejidadO\build\Debug\ComplejidadO.exe
```

Los resultados concretos cambian según los valores de entrada. La notación O
describe la tendencia de crecimiento, normalmente estudiada en el peor caso, no
la cantidad exacta de milisegundos de una ejecución.
