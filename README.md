# [Taller de Programación, Resumen para el Final.](https://jonathan-r0.github.io/taller.html)
## Cátedra Veiga, 2C 2020. 

Este resumen junta información relevante dictada durante las clases para la preparación del final. Ante algún error que se pueda detectar en este archivo, por favor mencionarlo.

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

# Clase 2

## [Sockets](https://raw.githubusercontent.com/Jonathan-R0/TallerDeProgramacion/master/TP1-9508/common_socket.c)

Siempre que se mande un mensaje por red, al destinatario del mismo se lo apoda `host`. Todo mensaje necesita conocer la ip y puerto de quien va a recibirlo. Para modelar la ip existen los protocolos iPv4 (codifica la ip con 4 bytes) e iPv6 (codifica la ip con 16 bytes).

El server hace un bind de su socket a su ip local (resultado de getaddrinfo) y le podemos decir al socket que escuche a una cierta cantidad de conexiones entrantes, a través de [`listen`](https://man7.org/linux/man-pages/man2/listen.2.html) por el sistema operativo. A este socket le pueden llegar conexiones que puede aceptar o no, y hasta entonces bloqueará la ejecución del programa.

Del lado del cliente creamos un socket que utilizamos para conectarnos con el servidor utilizando [`connect`](https://man7.org/linux/man-pages/man2/connect.2.html) hacia la dirección dada (obtenida con el [`getaddrinfo`](https://man7.org/linux/man-pages/man3/getaddrinfo.3.html)). Se manda el mensaje de conexión y se acepta, estableciendo la misma.

El servidor crea un segundo socket asociado al puerto y es el que acepta conexiones. Necesito uno de estos sockets extras por cada cliente con el que trabajo. Si llegan más pedidos que espacios en la pila, estos se pierden.

Para cerrar un canal de comunicación, lectura y/o escritura, se utiliza el [`shutdown`](https://man7.org/linux/man-pages/man2/shutdown.2.html).

### Protocolo TPC

Envia bytes, nunca streams. Además asegura que siempre llega la información sin bytes repetidos y respetando el orden de salida. 

Para satisfacer el protocolo correctamente debemos utilizar sockets, los cuales están diferenciados por su file descriptor. 

## Manejo de Archivos

Para manejar archivos en C podemos hacer principalmente dos cosas. Operamos con file descriptors o utilizamos la interfaz que nos provee el tipo FILE. En la materia usaremos el segundo.

Funciones importantes:

- [`FILE* fopen(const char* filepath, const char* mode);`](https://www.cplusplus.com/reference/cstdio/fopen/)
- [`size_t fread(void* ptr, size_t size, size_t count, FILE* fp );`](https://www.cplusplus.com/reference/cstdio/fread/)
- [`size_t fwrite(const void* ptr, size_t size, size_t count, FILE* fp );`](https://www.cplusplus.com/reference/cstdio/fwrite)
- [`int fseek(FILE* fp, long int offset, int origin);`](https://www.cplusplus.com/reference/cstdio/fseek/)
- [`int ftell(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/ftell/)
- [`void rewind(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/rewind/)
- [`int getc(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/getc/)
- [`int putc(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/putc/)
- [`char* fgets(const char* str, int n, FILE* fp);`](https://www.cplusplus.com/reference/cstdio/fgets/)
- [`int fputs(const char* str, FILE* fp);`](https://www.cplusplus.com/reference/cstdio/fputs/)
- [`int feof(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/feof/)
- [`int ftruncate(FILE* fp, long int offset);`](https://linux.die.net/man/2/ftruncate)
- [`int fclose(FILE* fp);`](https://www.cplusplus.com/reference/cstdio/fclose/)

Los modos de apertura de archivos en C son los siguientes:

- `r`: Lectura. El archivo debe existir.
- `w`: Escritura. Crea el archivo si no existe, de lo contrario lo sobreescribe.
- `a`: Escritura al final. Crea el archivo si no existe.
- `r+`: Lectura y escritura al principio. El archivo debe existir.
- `w+`: Lectura y escritura. Sobreescribe el archivo si existe.
- `a+`: Lectura y escritura al final del mismo.
- `b`: Para que se trabajen sobre archivos binarios.
- `t`: Para archivos de texto.

# Clase 7

## SDL

Un programa que inicializa una ventana es la siguiente:

```
int main(int argc, char* argv[]) {
  SDL_INIT(SDL_INIT_VIDEO);
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_RENDERER_ACCELERATED, &window, &renderer);
  SDL_Event event;

  bool running = true;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) running = false;
    }
    doCoolStuff(window, renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
```

Podemos utilizar funciones como [`SDL_GetWindowSize`](https://wiki.libsdl.org/SDL_GetWindowSize), [`SDL_SetRenderDrawColor`](https://wiki.libsdl.org/SDL_SetRenderDrawColor), [`SDL_DrawLine`](https://wiki.libsdl.org/SDL_DrawLine), [`SDL_RenderClear`](https://wiki.libsdl.org/SDL_RenderClear) y [`SDL_RenderPresent`](https://wiki.libsdl.org/SDL_RenderPresent).

# Clase 8

## Namespaces

Nos permite diferenciar instancias y variables. Por ejemplo:

```
namespace Black {
  class Cat { ... }
}

namespace Orange {
  class Cat { ... }
}
```

Nos permite diferenciar entre `Black::Cat` y `Orange::Cat`.

Si un namespace es anónimo, cualquier instancia de lo que se encuentre adentro del mismo podrá existir en el módulo en que se lo definió. Eso permite generar una funcionalidad similar a la de _static_.

La keyword `using`, al utilizarla con namespaces nos permite obviar la mención de estos en nustros módulo de código. 

## Friendship

Nos permite acceder a atributos privados de nuestros "amigos". No se hereda. Un buen ejemplo está en el siguiente código, donde implementamos un método que nos permite imprimir los valores de nuestra clase Stack, sin tener getters.

```
class Stack {
  ...
  friend std::ostream& operator<< (std::ostream& stream, const Stack& stack) {
    stream << "[";
    int len = stack.buffer.size();
    for (int i = 0; i < len; i++) {
      stream << stack.buffer[i];
    }
    stream << "]";
    return stream;
  }
}
```
