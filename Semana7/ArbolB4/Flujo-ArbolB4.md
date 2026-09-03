# Flujo de `ArbolB4` — cómo se relacionan los métodos

Este documento no explica *qué hace cada línea* (eso ya está comentado
dentro de `ArbolB4.cpp`). Explica algo distinto y más útil para entender
la metodología completa: **qué método llama a cuál, en qué orden, y por
qué** — el mapa de decisiones que recorre el código cada vez que se
inserta, elimina o busca un amigo.

## La idea que gobierna todo el archivo

Antes de mirar los tres flujos por separado, hay una sola idea que
explica el 90% de las decisiones de diseño de `ArbolB4`:

> **Arreglar el problema ANTES de bajar un nivel, nunca después.**

- Al insertar: si el hijo al que voy a bajar está **lleno**, lo divido
  *antes* de bajar (`dividirHijo`).
- Al eliminar: si el hijo al que voy a bajar está **al límite**, lo
  relleno *antes* de bajar (`llenarHijo`).

Esto es lo opuesto a como funciona `ArbolAVL` (Semana 6), que primero deja
que la recursión baje hasta el fondo, y recién **al volver** ("deshaciendo
el camino") corrige cada nivel con `balancear()`. `ArbolB4` corrige **en
el camino de ida**, nunca en el de vuelta — por eso ninguna de sus
funciones recursivas necesita devolver información especial hacia arriba
(a diferencia de `ArbolAVL::insertar(Nodo*, ...)`, que devuelve `Nodo*`
para que el nivel de arriba reenganche el subárbol posiblemente rotado).

Con esa idea en mente, los tres flujos siguientes son mucho más fáciles de
leer.

## 1. Flujo de `insertar(nombre, edad)`

```
insertar(nombre, edad)                         [PUBLICO]
│
├─ buscar(edad)                                 → si ya existe, return false
│
├─ ¿raiz == nullptr?
│     └─ sí → crearNodo(esHoja=true), esa es la raiz
│
├─ ¿raiz esta LLENA? (cantidadClaves == MAX_CLAVES)
│     └─ sí → nuevaRaiz = crearNodo(esHoja=false)
│             nuevaRaiz.hijos[0] = raiz
│             dividirHijo(nuevaRaiz, 0)   ← la raiz vieja se parte aqui
│             raiz = nuevaRaiz             ← el arbol CRECIO en altura
│
└─ insertarEnNodoNoLleno(raiz, nombre, edad)    [privado, hace el trabajo real]
      │
      ├─ ¿nodo es hoja?
      │     └─ sí → desplazar claves mayores a la derecha
      │             escribir (nombre, edad) en el hueco
      │             ++cantidadClaves
      │             (aqui termina la recursion: caso base)
      │
      └─ ¿nodo es interno?
            ├─ buscar el indice `i` del hijo por el que hay que bajar
            ├─ ¿hijos[i] esta LLENO?
            │     └─ sí → dividirHijo(nodo, i)     ← se arregla ANTES de bajar
            │             ¿la clave promovida es menor que `edad`?
            │                 └─ sí → ++i  (bajar por el hermano nuevo, no el viejo)
            └─ insertarEnNodoNoLleno(hijos[i], nombre, edad)   ← RECURSION
```

**Quién llama a quién:**

| Método | Lo llama | Llama a |
|---|---|---|
| `insertar()` | `main()` | `buscar()`, `crearNodo()`, `dividirHijo()`, `insertarEnNodoNoLleno()` |
| `insertarEnNodoNoLleno()` | `insertar()`, a sí misma | `dividirHijo()`, a sí misma (recursión) |
| `dividirHijo()` | `insertar()`, `insertarEnNodoNoLleno()` | `crearNodo()` |

**Por qué crece la altura solo en un lugar**: la única línea de todo el
archivo que hace crecer la altura del árbol es `raiz = nuevaRaiz` dentro
de `insertar()`. `insertarEnNodoNoLleno()` nunca lo hace — no puede,
porque para cuando se la llama, ya se garantizó que hay lugar. Por eso
alcanza con leer `insertar()` para entender *cuándo* crece el árbol, sin
tener que rastrear la recursión completa.

## 2. Flujo de `eliminar(edad)`

Es el espejo del flujo de inserción, cambiando "lleno → dividir" por
"al límite → rellenar":

```
eliminar(edad)                                 [PUBLICO]
│
├─ ¿raiz == nullptr? o ¿!buscar(edad)?
│     └─ sí → return false (no existe, no hay nada que hacer)
│
├─ eliminarDeNodo(raiz, edad)                   [privado, hace el trabajo real]
│     │
│     ├─ buscar el indice `i`: ¿la clave esta EN este nodo?
│     │
│     ├─ SI esta en este nodo:
│     │     ├─ ¿es hoja?
│     │     │     └─ sí → quitar del arreglo, correr claves a la izquierda
│     │     │             (aqui termina: caso base)
│     │     └─ ¿es interno?
│     │           └─ eliminarDeNodoInterno(nodo, i)
│     │                 ├─ ¿hijos[i] tiene de sobra? (> MIN_CLAVES)
│     │                 │     └─ usar PREDECESOR: obtenerMaximoNodo(hijos[i])
│     │                 │        copiar su clave sobre nodo->edades[i]
│     │                 │        eliminarDeNodo(hijos[i], edadDelPredecesor)  ← RECURSION
│     │                 ├─ si no, ¿hijos[i+1] tiene de sobra?
│     │                 │     └─ usar SUCESOR: obtenerMinimoNodo(hijos[i+1])
│     │                 │        copiar su clave sobre nodo->edades[i]
│     │                 │        eliminarDeNodo(hijos[i+1], edadDelSucesor)   ← RECURSION
│     │                 └─ si ninguno tiene de sobra:
│     │                       fusionarHijos(nodo, i)
│     │                       eliminarDeNodo(hijos[i], edadOriginal)          ← RECURSION
│     │
│     └─ NO esta en este nodo (hay que bajar por hijos[i]):
│           ├─ ¿hijos[i] esta AL LIMITE? (cantidadClaves == MIN_CLAVES)
│           │     └─ sí → i = llenarHijo(nodo, i)     ← se arregla ANTES de bajar
│           │                 ├─ ¿hermano izquierdo tiene de sobra?
│           │                 │     └─ prestarDeIzquierda(nodo, i)
│           │                 ├─ si no, ¿hermano derecho tiene de sobra?
│           │                 │     └─ prestarDeDerecha(nodo, i)
│           │                 └─ si ninguno tiene de sobra:
│           │                       fusionarHijos(nodo, i) o (nodo, i-1)
│           │                       (el indice de retorno puede cambiar a i-1)
│           └─ eliminarDeNodo(hijos[i], edad)   ← RECURSION
│
└─ ¿raiz se quedo con 0 claves?
      └─ sí → raiz = ¿era hoja? nullptr : hijos[0]
              delete raizVieja                  ← el arbol ACHICO su altura
```

**Quién llama a quién:**

| Método | Lo llama | Llama a |
|---|---|---|
| `eliminar()` | `main()` | `buscar()`, `eliminarDeNodo()` |
| `eliminarDeNodo()` | `eliminar()`, a sí misma, `eliminarDeNodoInterno()` | `eliminarDeNodoInterno()`, `llenarHijo()`, a sí misma |
| `eliminarDeNodoInterno()` | `eliminarDeNodo()` | `obtenerMaximoNodo()`, `obtenerMinimoNodo()`, `fusionarHijos()`, `eliminarDeNodo()` |
| `llenarHijo()` | `eliminarDeNodo()` | `prestarDeIzquierda()`, `prestarDeDerecha()`, `fusionarHijos()` |
| `prestarDeIzquierda()` / `prestarDeDerecha()` | `llenarHijo()` | (nada — son hojas del árbol de llamadas) |
| `fusionarHijos()` | `llenarHijo()`, `eliminarDeNodoInterno()` | `delete` directo (libera el hermano absorbido) |

**Por qué la altura se achica solo en un lugar**: igual que con
`insertar()`, la única línea que reduce la altura del árbol es
`raiz = hijos[0]` dentro de `eliminar()`. Ninguna función privada lo hace
por su cuenta.

**El caso más denso — `eliminarDeNodoInterno`**: es el único punto donde
`eliminarDeNodo` se llama a sí misma con una clave **distinta** a la que
se pidió eliminar originalmente (la del predecesor, el sucesor, o —
después de fusionar — la clave original, que ahora vive en un nodo
distinto). Vale la pena que los estudiantes sigan este caso con un
`std::cout` temporal o el depurador para verlo con sus propios ojos.

## 3. Flujo de `buscar(edad)`

El más simple de los tres, y el único que **no modifica** el árbol —
por eso tanto `insertar()` como `eliminar()` lo usan como primer paso,
sin preocuparse de que tenga efectos secundarios:

```
buscar(edad)                                   [PUBLICO]
└─ buscar(raiz, edad)                          [privado, recursivo]
      ├─ ¿nodo == nullptr? → return nullptr (no existe)
      ├─ recorrer las claves de nodo buscando `edad` o el hijo por donde seguir
      ├─ ¿se encontro en ESTE nodo? → return nodo
      ├─ ¿nodo es hoja? → return nullptr (no existe, no hay donde mas buscar)
      └─ return buscar(hijos[i], edad)          ← RECURSION
```

`insertar()` lo usa para **rechazar duplicados** antes de tocar la
estructura. `eliminar()` lo usa para **confirmar que la clave existe**
antes de arrancar el algoritmo de eliminación (que asume, en todas sus
funciones privadas, que la clave que busca SI está en alguna parte del
subárbol — nunca tiene que lidiar con el caso "no existe" en medio del
proceso).

## Tabla resumen: qué dispara cada operación

| Situación | Operación disparada | Función responsable |
|---|---|---|
| Insertar en un nodo lleno | Dividir el nodo en dos, promover la clave del medio | `dividirHijo()` |
| Insertar cuando la raíz está llena | Crecer el árbol un nivel | `insertar()` (crea `nuevaRaiz`) |
| Eliminar y un hermano tiene claves de sobra | Pedir prestada una clave, rotando por el padre | `prestarDeIzquierda()` / `prestarDeDerecha()` |
| Eliminar y ningún hermano tiene de sobra | Fusionar dos nodos en uno | `fusionarHijos()` |
| Eliminar una clave que vive en un nodo interno | Reemplazar por predecesor, sucesor, o fusionar | `eliminarDeNodoInterno()` |
| Eliminar y la raíz se queda sin claves | Achicar el árbol un nivel | `eliminar()` (reasigna `raiz`) |

## Orden recomendado para leer `ArbolB4.cpp` por primera vez

No es el mismo orden en que aparecen las funciones en el archivo — este
orden sigue la lógica de "de lo simple a lo complejo":

1. `crearNodo()`, `liberar()` — lo básico, ya conocido de semanas
   anteriores.
2. `buscar()` (ambas versiones) — no modifica nada, fácil de seguir.
3. `dividirHijo()` — la operación más importante de la inserción.
4. `insertarEnNodoNoLleno()` y `insertar()` — cómo se usa `dividirHijo()`
   en la práctica.
5. `obtenerMaximoNodo()` / `obtenerMinimoNodo()` — simples, preparan el
   terreno para lo que sigue.
6. `prestarDeIzquierda()` / `prestarDeDerecha()` — antes de fusionar,
   porque son más simples.
7. `fusionarHijos()` — la operación más importante de la eliminación.
8. `llenarHijo()` — cómo se decide entre prestar y fusionar.
9. `eliminarDeNodoInterno()` y `eliminarDeNodo()` — cómo se usa todo lo
   anterior en la práctica.
10. `altura()`, `mostrarEnOrden()`, `generarNodosDot()` — utilidades de
    lectura, no cambian la estructura.

## Nota sobre Git

Este archivo vive en `GuiasAux/`, que está en el `.gitignore` de la raíz
del repositorio: es material auxiliar local y Git no lo agrega al
repositorio.
