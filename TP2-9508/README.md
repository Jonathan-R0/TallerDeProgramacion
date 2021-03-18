# Taller de Programación I - Cátedra Veiga - FIUBA
# Trabajo Práctico II 

<h2 align="right">Jonathan David Rosenblatt</h2>
<h2 align="right">104105</h2>

## Introducción

Este es el segundo trabajo práctico de la materia en el que se debe entregar un producto programado y documentado. El mismo fue programado en C++ y requiere conocimientos en este lenguaje (además de ser capaz de adaptarse a los cambios que este trae sobre el lenguaje C) además de conocimientos en la programación multi-hilos. Un objetivo de este tp es nivelar la capacidad de programación en C++ del alumnado, adquiriendo buenas prácticas y escribiendo buen código en el camino.

## Configuración del Proyecto

Para configurar y ejecutar el código lo primero que se debe hacer es clonar el repositorio. Luego para compilar y enlazar se debe ejecutar el Makefile incluido (ejecutando ```make```). En caso de tener errores con el compilador o el enlazador se verán escritos por stderr.

Se debe ejecutar con 

```
./tp <NUMBER-OF-THREADS> <FILE-1> <FILE-2> ... <FILE-N>
```

Siendo:

- ```<NUMBER-OF-THREADS>```: El número de hilos con los que se va a ejecutar el programa
- ```<FILE-i>```: El i-ésimo archivo a procesar.

***Aclaración: no necesariamente se debe tener un hilo por archivo.***

## Diseño y Clases

La naturaleza de este programa requiere la existencia de una clase thread. Esta clase abstracta implementa todos los métodos necesarios para que este funcione y particularmente tenemos el método abstracto run, el cual es redefinido por el eBPF para que cada hilo pueda ejecutar de forma concurrente sus tareas.

El eBPF tiene a las clases fileRepository y results para obtener y guardar la información de la lectura de cada archivo, respectivamente. 

Luego la clase graphFiller actua como una abstracción para el eBPF. Esto permite encapsular al grafo, parser y gestor de información de línea (clase asmline).

Diagrama de clases general del programa:

<br><p align="center"><img src="img/classdiag.png"/></p> 

Diagrama de secuencia del programa cuando se lo llama para leer n archivos, de principio a fin:

<br><p align="center"><img src="img/seqdiag.png"/></p> 

## Herramientas Utilizadas

Las herramientas más utilizadas en este tp fueron:

- ***Valgrind***: el glorioso programa que tanto nos ayuda a debuggear el código. Con flags como ```--track-origins=yes``` para ver donde se nos generan variables no inicializadas que puedan causar problemas, entre otros.

- ***Gdb***: el debugger de GNU, súper útil para revisar con detalle el código y encontrar más facilmente la causa de problemas como segmentation faults, loops infinitos, entre otros.

## Cambios Importantes de la Reentrega

- El primer gran cambio es la creación de la clase `Executer`. La misma le permite al `main()` delegarle las tareas que antes tenía, para que el mismo no contenga ningún tipo de lógica innecesaria. Este contiene las referencias a los hilos creados y se encarga de crearlos, iniciarlos y luego destruirlos.

- La clase `Asmline`, que antes ingresaba al parser para ser completada con la información que este procesaba, es ahora creada por la misma entidad y devuelta al finalizar de procesar la línea ingresada. La devolución se hace por movimiento. Esto permite eliminar algunos de los setters que utiliza, para poder inicializar el objeto con ingresando datos con el ***Member initializer list***.

- Dentro de la clase `EBPF` se añade una pequeña optimización, donde se pasa el string "filename" hacia el repositorio de respuestas por movimiento. Otro cambio del estilo ocurre en el método `init` de la misma clase, donde ahora se envia la información leída por movimiento, evitando así copias innecesarias.

- En el .cpp de la clase `Graph` se cambian la mayoría de las iteraciones rústicas por usos de funciones de la ***Standard Template Library***. 

- Finalmente en la clase `Parser` se realizó una refactorización del método de parseo de líneas. Se evitan utilizan strings y listas de más, que lo único que hacen es comer más memoria, además de aprovechar mejor los métodos de la ***Standard Template Library***.
