# Semana 2 — Ejemplo Qt (ContadorQt)

Ejemplo mínimo de una aplicación de escritorio con **Qt Widgets** en C++: una
ventana con una etiqueta y dos botones ("Sumar" / "Reiniciar") que
incrementan o reinician un contador. Sirve para introducir `QApplication`,
`QWidget`, layouts y el mecanismo de señales y slots.

## Archivos fuente (lo único que se escribe a mano)

- `CMakeLists.txt`: configuración para que CMake encuentre Qt y compile el
  ejecutable.
- `ContadorQt/ContadorWindow.h`: declaración de la ventana.
- `ContadorQt/ContadorWindow.cpp`: implementación (construcción de la
  interfaz y lógica del contador).
- `ContadorQt/main.cpp`: punto de entrada (`QApplication` + mostrar la
  ventana).
- `flujoComandos.txt`: chuleta con los comandos exactos para configurar,
  compilar y ejecutar en esta máquina.

Todo lo demás que aparece en esta carpeta (`build-mingw/`) **no se edita a
mano**: lo genera el propio proceso de compilación y se puede borrar y
regenerar en cualquier momento con los comandos de `flujoComandos.txt`.

## Qué es cada cosa dentro de `build-mingw/`

Esta carpeta la crea `cmake -B build-mingw` y se llena en dos pasos:
**configurar** (`cmake -S . -B build-mingw ...`), **compilar**
(`cmake --build build-mingw`) y **desplegar las DLLs de Qt**
(`windeployqt`).

### Generados por la configuración de CMake

- `CMakeCache.txt`: guarda las respuestas que CMake ya averiguó (dónde está
  el compilador, dónde está Qt, etc.) para no tener que redescubrirlas cada
  vez. Si cambias de compilador o de ruta de Qt y algo no cuadra, borrar
  esta carpeta entera y volver a configurar desde cero suele arreglarlo.
- `CMakeFiles/`: archivos internos que usa CMake para llevar el control de
  dependencias. No se tocan a mano.
- `cmake_install.cmake`: script de instalación que CMake genera por
  defecto en todo proyecto, aunque aquí no lo usemos (no hacemos `make
  install`).

### Generados por Ninja (el sistema de build)

- `build.ninja`: es el equivalente a un Makefile — la lista de comandos
  exactos que hay que correr, y en qué orden, para producir el `.exe`.
- `.ninja_log` / `.ninja_deps`: bases de datos internas que Ninja usa para
  saber qué archivos cambiaron desde el último build, así solo recompila
  lo necesario (build incremental).

### Generados por Qt (moc)

- `ContadorQtGuia_autogen/`: código C++ adicional que Qt genera
  automáticamente a partir de `Q_OBJECT` en `ContadorWindow.h` (lo hace la
  herramienta *moc*, activada por `CMAKE_AUTOMOC` en el `CMakeLists.txt`).
  Es lo que hace que `connect()` con señales y slots funcione.

### El resultado de compilar

- `ContadorQtGuia.exe`: el programa ya compilado.

### Generados por `windeployqt` (el paso de "empaquetado")

`windeployqt` analiza el `.exe`, detecta qué módulos de Qt usa, y copia todo
lo necesario para que corra sin tener Qt instalado en el `PATH`:

- `Qt6Core.dll`, `Qt6Gui.dll`, `Qt6Widgets.dll`, `Qt6Network.dll`,
  `Qt6Svg.dll`: las librerías de Qt que usa el programa.
- `libgcc_s_seh-1.dll`, `libstdc++-6.dll`, `libwinpthread-1.dll`: librerías
  del propio compilador MinGW que el ejecutable necesita en tiempo de
  ejecución.
- `opengl32sw.dll`, `D3Dcompiler_47.dll`: soporte de renderizado gráfico por
  software, por si la tarjeta gráfica no puede acelerar el dibujo de la
  interfaz.
- `platforms/`, `styles/`, `imageformats/`, `iconengines/`, `generic/`,
  `networkinformation/`, `tls/`: plugins de Qt que se cargan en tiempo de
  ejecución según el sistema operativo. La más importante es `platforms/`
  (trae `qwindows.dll`): sin ella la aplicación ni siquiera puede abrir una
  ventana en Windows.
- `translations/`: archivos `.qm` con las traducciones de los textos
  internos de Qt (botones de diálogos estándar, etc.) a distintos idiomas.

## Flujo completo

Ver `flujoComandos.txt` para los comandos ya probados en esta máquina. En
resumen:

```text
1. Configurar   → cmake -S . -B build-mingw -G "Ninja" -DCMAKE_PREFIX_PATH=...
2. Compilar     → cmake --build build-mingw
3. Empaquetar   → windeployqt build-mingw\ContadorQtGuia.exe
4. Ejecutar     → build-mingw\ContadorQtGuia.exe
```

Los pasos 1 y 3 solo hay que repetirlos si borras `build-mingw/` o cambias
el `CMakeLists.txt`. En el día a día, después de editar código, basta con
repetir los pasos 2 y 4.

> El compilador MinGW de Qt (`C:\Qt\Tools\mingw1310_64\bin`) necesita estar
> en el `PATH` de la terminal antes de correr `cmake`, si no la
> compilación falla sin un mensaje de error claro.

## Nota sobre Git

`build-mingw/` está ahora en el `.gitignore` de la raíz del repositorio:
es contenido 100% regenerable a partir del código fuente y no tiene sentido
versionar binarios ni DLLs de terceros.
