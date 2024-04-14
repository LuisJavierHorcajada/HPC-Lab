## Autores

-   Luis Javier Horcajada Torres - [LuisJavier.Horcajada\@alu.uclm.es](mailto:LuisJavier.Horcajada@alu.uclm.es)
-   Antonio Dominguez Martin - [Antonio.Dominguez5@alu.uclm.es](mailto:Antonio.Dominguez5@alu.uclm.es)

## Guía de instalación

Para el correcto funcionamiento del programa se deben cumplir estos requisitos:

-   Python3
-   Librerias opencv y numpy
-   El código fuente **kmeans_MPI_final**
-   El archivo con los valores de cada pixel **pavia.txt**

## Guía de ejecución

La ejecución del programa es muy sencilla, en primer lugar, vamos a explicar los argumentos que tenemos que pasar:

### Argumentos obligatorios

-   -k: Este argumento indica el número de clusters que se van a ejecutar, si por ejemplo ponemos *-k 3* estaremos indicando que lanzar 3 clusters.
-   -i: El número máximo de iteraciones que va a ejecutar el kmeans.

### Argumentos de ayuda

-   -h: Este argumento sirve para ver todos los detalles de los argumentos que se pueden pasar, **si se utiliza, el programa no se ejecutará y mostrará la ayuda**.

## Ejemplos de ejecución

El ejemplo general de cómo ejecutar el programa es *mpiexec -n [número de procesos]python3 kmeans_MPI_final -k [número de clusters] - i [número de iteraciones]*

Algunos ejemplos:

-   mpiexec -n 6 python3 kmeans_MPI_final -k 10 - i 100
-   mpiexec -n 12 --oversubscribe python3 kmeans_MPI_final -k 4 - i 1000
-   mpiexec -n 8 python3 kmeans_MPI_final -k 7 - i 200

## Ejecución automatizada

Ejecutar el archivo **run_kmeans.sh**, este ejecutará de manera automática el archivo .py con k = 10, i =100, n = 4

## Ejecución finaliza

Se indicarán la cantidad de segundos que han sido necesitados para llevar a cabo el algorítmo kmeans con *k* clusters y *n* procesos.
