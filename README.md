# Taller de Programación, Resumen para el Final.
## Cátedra Veiga, 2C 2020. 

Este resumen intenta juntar información relevante dictada durante las clases para la preparación del final. Ante algún error que se pueda detectar en este archivo, por favor mencionarlo.

# Clase 1

## Memoria

- Llamamos ***alineación*** al hecho de que las variables siempre deben arrancar a estar en posiciones de memoria que sean múltiplos del tamaño de las mismas. Esto se hace por una cuestión de eficiencia y por lo tanto hace que muchos arreglos de datos desperdicien a próposito bytes para mantener esta estructura. 

- Aquellos pedazos de memoria que dejamos sin usar que nos ayuda a alinear la memoria se conoce como ***padding***.

- Recordamos que el tamaño de los datos está definido por la ISA de la arquitectura que utiliza nuestro computador.

## Structs & Unions

Un ejemplo donde vemos como se manifiesta el padding, es con los ***structs & unions***. Sea el siguiente ejemplo en una arquitectura x86 de 64b:

```
struct S {
    int a;         |A|A|A|A|
    char b;        |B| | | |
    int c;         |C|C|C|C| | | | |
    short d;       |D|D|D|D|D|D|D|D|
};                
```

Donde `a` ocupa los bytes 0,1,2 y 3 del mismo y luego `b` está en el byte 4 (siempre relativo al inicio de la estructura). Pero `c` no comienza en el byte 5, comienza en el 8, dejando tres bytes de padding pues necesita que el byte donde arranca sea un múltiplo de su tamaño (es decir 4). Por lo tanto antes de poner a `d` tenemos que dejar 4 bytes más de padding así puede arrancar en la dirección 16.

Esto es diferente con los unions donde el tamaño de la estructura general es el tamaño de su miembro más pesado y donde todos los datos viven en el mismo espacio de memoria.

Podemos agregar `__atribute__((packed));` antes de terminar de definir el struct para que esté no agregué padding al mismo.

Si tenemos: 

```
union U {
    long l;
    int* p;
};
```

La estructura general pesará 8 bytes pues si accedo a `l` estaré leyendo el número que luego `p` interpreta como una dirección de memoria.

## Ajuste de Endianness

Para ajustar el endianness de nuestros datos cuando estos pasan por sockets por ejemplo, es con este conjunto de funciones:

````
short int htons(short int);
short int ntohs(short int);
int htonl(int);
int ntohl(int);
````

Siendo `hton` host-to-network, `ntoh` network-to-host y el último caracter indica si es un short o int el dato con el que trabaja.

Si recibo un dato debería pasarlo por `ntoh` y si lo mando `hton` para ajustar el endianness.

## Segmentos de Memoria

***Code Segment***: De lectura y ejecución. Para código y constantes. No redefinible.

***Data Segment***: Variables creadas al inicio del programa y son válidas hasta que termina la ejecución del programa. De acceso global o local. No redefinible.

***Stack***: Variables creadas al inicio del scope en el que este existe. Los datos se destruten al salir de este.

***Heap***: Variables compartidas por todos los programas de la máquina.

## Lifetime y Scope

```
int g = 1;         // Data segment, scope global.
static int l = 2;  // Data segment, scope local.
extern int e;      // No asigna memoria, simplemente es una definición. 

void Fg() {}       // Code segment, scope global. 
void Fl() {}       // Code segment, scope local.
void Fe();         // No asigna memoria, simplemente es una definición.

void foo() {
    int localStack = 1;
    static int localDataSegment = -1;
    char* pointingToTheCodeSegment = "ABC";
    char stackArray[] = "ABC";
}

```

- Para utirlizar a `e`, el mismo tiene que en alguna parte del programa haber sido definido para no leer algo ni inicializado.
- Los punteros a función apuntan al code segment.

# Compilación

Decimos que C/C++ son lenguajes portables pues estos pueden crear código ejecutable hacia cualquier tipo de arquitectura (siempre tendiendo en cuenta el tipo de compilador que parsea y genera el ejecutable).

El proceso de compilación tiene varias etapas:

***Precompilación***: Se realizan tareas relacionadas con el reemplazo de variables, búsqueda de código fuente y un parseo de texto general. Todo lo que tiene que ver con manejo de archivos, headers, etc se resuelve acá. Si compilamos en C, solo le llegarán `.c` a la etapa de compilación. Reemplaza en el código los defines correspondientes, en función de las reglas definidas por los rótulos dados (`include, ifndef, define, ifdef, endif, ...`).

***Compilación***: Verificación del código suministrado. Genera un código objeto. Los `.c` que reciben se transforman en `.o` & `.lib`.

***Link-Edición***: Combina los distintos códigos objetos, librerías externas, resuelve problemas de referencias cruzadas y genera el ejecutable correspondiente a la plataforma en la que se realiza esto. Para generar un ejecutable más pequeño se puede realizar un *linkeo dinámico*. Esto consiste de linkear código objeto ya pregenerado que es usado por varios programas. Estas librerias dinámicas se encuentran una vez en la memoria del sistema y permite ahorrar memoria. Puede correr más rápido si este código ya está cacheado por otro programa que lo utilizó hace relativamente poco.