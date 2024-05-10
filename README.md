## Autores

-   Luis Javier Horcajada Torres - [LuisJavier.Horcajada\@alu.uclm.es](mailto:LuisJavier.Horcajada@alu.uclm.es)
-   Antonio Dominguez Martin - [Antonio.Dominguez5@alu.uclm.es](mailto:Antonio.Dominguez5@alu.uclm.es)

## Directorios

-  hito1: En el hito1 se encuentra el desarrollo e implementación del algoritmo kmeans en python.
-  hito2: En el hito2 se encuentra el desarrollo e implementación del kmeans de manera **paralela** utilizando **MPI** en python.
-  hito3: En el hito3 se encuentra desarrollo e implementación del kmeans de manera **paralela** utilizando **OpenMP** en C++.

## Hito 1

### Guía de instalación

Para el correcto funcionamiento del programa se deben cumplir estos requisitos:

-   Python3
-   Librerias opencv y numpy
-   El código fuente **kmeansPropio**
-   El archivo con los valores de cada pixel **pavia.txt**
    -   Se puede descargar aquí: [pavia.txt](https://drive.google.com/file/d/1XkSp7vMsTrp9aTY40RtZhVqdZPMyguwM/view)


### Guía de ejecución

La ejecución del programa es muy sencilla, en primer lugar, vamos a explicar los argumentos que tenemos que pasar:

#### Argumentos obligatorios

-   -k: Este argumento indica el número de clusters que se van a ejecutar, si por ejemplo ponemos *-k 3* estaremos indicando que lanzar 3 clusters.
-   -i: El número máximo de iteraciones que va a ejecutar el kmeans.

#### Argumentos de ayuda

-   -h: Este argumento sirve para ver todos los detalles de los argumentos que se pueden pasar, **si se utiliza, el programa no se ejecutará y mostrará la ayuda**.

#### Ejemplos de ejecución

El ejemplo general de cómo ejecutar el programa es *python3 kmeansPropio -k [número de clusters]*

Algunos ejemplos:

-   python3 kmeansPropio -k 3
-   python3 kmeansPropio -k 2
-   python3 kmeansPropio -k 5

### Ejecución automatizada

Ejecutar el archivo **run_kmeans.sh**, este ejecutará de manera automática el archivo .py con k = 3

### Ejecución finaliza

Se indicarán la cantidad de segundos que han sido necesitados para llevar a cabo el algorítmo kmeans con *k* clusters.

## Hito 2

### Ficheros:

Se encuentran varios ficheros con distintas versiones que se fueron desarrollando a lo largo del hito, todas se pueden probar pero la final es **kmeans_MPI_final**.

### Ejemplos de ejecución

El ejemplo general de cómo ejecutar el programa es *mpiexec -n [número de procesos]python3 kmeans_MPI_final -k [número de clusters] - i [número de iteraciones]*

Algunos ejemplos:

-   mpiexec -n 6 python3 kmeans_MPI_final -k 10 - i 100
-   mpiexec -n 12 --oversubscribe python3 kmeans_MPI_final -k 4 - i 1000
-   mpiexec -n 8 python3 kmeans_MPI_final -k 7 - i 200

## Hito 3

### Ficheros

- Makefile: Contiene el makefile para la ejecución automatizada de los archivos.
- kmeans_c++.cpp: Contiene el archivo con el algoritmo de kmeans implementado en C++, se ha intentado mantener lo más similar posible al desarrollado en el hito 1 en python para su comparación.
- kmeans_OMP.cpp: Contiene el archivo con el algoritmo de kmeans implementado y paralelizado mediante **OpenMP**.
- slurm.sh: Contiene el __jobscript__ para que se pueda ejecutar la versión paralelizado en un cluster de slurm.

### Guía de ejecución

La ejecución se realiza mediante el Makefile:

-  **make** para compilar todos los archivos.
-  **make run** ejecutará la versión paralelizada con 10 clusters y 200 iteraciones.
-  **make run_OMP** para ejecutar la versión paralelizada con argumentos personalizados.
   -  Ejemplo: make run_OMP ARGS="-k 8 -i 120"
- **make run_sequential_example** ejecuta la versión secuencial con 10 clusters y 200 iteraciones.
- **make run_sequential** ejecuta la versión secuencial con argumentos personalizados.
  -  Ejemplo: make run_sequential ARGS="-k 9 -i 175"
- **make clean** limpia todos los ejecutables y directorios creados por el __Makefile__.
