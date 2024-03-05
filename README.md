## Autores

-   Luis Javier Horcajada Torres - [LuisJavier.Horcajada\@alu.uclm.es](mailto:LuisJavier.Horcajada@alu.uclm.es)
-   Antonio Dominguez Martin - [Antonio.Dominguez5@alu.uclm.es](mailto:Antonio.Dominguez5@alu.uclm.es)

## Guía de instalación

Para el correcto funcionamiento del programa se deben cumplir estos requisitos:

-   Python3
-   Librerias opencv y numpy
-   El código fuente **kmeans_propio**
-   El archivo con los valores de cada pixel **pavia.txt**

## Guía de ejecución

La ejecución del programa es muy sencilla, en primer lugar, vamos a explicar los argumentos que tenemos que pasar:

### Argumentos obligatorios

-   -k: Este argumento indica el número de clusters que se van a ejecutar, si por ejemplo ponemos *-k 3* estaremos indicando que lanzar 3 clusters.

### Argumentos de ayuda

-   -h: Este argumento sirve para ver todos los detalles de los argumentos que se pueden pasar, **si se utiliza, el programa no se ejecutará y mostrará la ayuda**.

## Ejemplos de ejecución

El ejemplo general de cómo ejecutar el programa es *python3 kmeans_propio -k [número de clusters]*

Algunos ejemplos:

-   python3 kmeans_propio -k 3
-   python3 kmeans_propio -k 2
-   python3 kmeans_propio -k 5

## Ejecución finaliza

Se indicarán la cantidad de segundos que han sido necesitados para llevar a cabo el algorítmo kmeans con *k* clusters.
