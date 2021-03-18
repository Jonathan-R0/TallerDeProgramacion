// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <stddef.h>

typedef struct socket {
  int fd;
} socket_t;

/*
 * Inicializa el socket con fd en -1, es decir, es inválido por default;
 * Precondiciones: socket != NULL.
 * Postcondiciones: deja el socket inicializado. Devuelve -1 en caso de error, 0
 * de lo contrario.
 */
int socket_init(socket_t* socket);

/*
 * Destruye el socket, cortando la conexión y cerrando el fd.
 * Precondiciones: socket != NULL.
 * Postcondiciones: Corta la conexión y devuelve los recursos al OS. Devuelve -1
 * en caso de error, 0 de lo contrario.
 */
int socket_destroy(socket_t* socket);

/*
 * Conecta un el socket dado al puerto e ip especificados. Conecta al primer
 * puerto que encuentra válido.
 * Precondiciones: socket != NULL && port != NULL.
 * && ip != NULL.
 * Postcondiciones: Conecta el socket al servidor. Devuelve -1 en
 * caso de error, 0 de lo contrario.
 */
int socket_connect(socket_t* socket, const char* port, const char* ip);

/*
 * Enlaza el socket con el puerto ingresado. Enlaza al primer puerto válido.
 * Precondiciones: socket != NULL && port != NULL.
 * Postcondiciones: . Devuelve -1 en caso de error, 0 de lo contrario.
 */
int socket_bind(socket_t* socket, char* port);

/*
 * Wrapper para listen(2). Verifica que el socket es válido.
 * Precondiciones: socket != NULL
 * Postcondiciones: ejecuta listen(2). Devuelve -1 en caso de error y llama al
 * destructor, 0 de lo contrario.
 */
int socket_listen(socket_t* socket, unsigned int queueSize);

/*
 * Wrapper para accept(2). Verifica que el socket y puerto sean válidos.
 * Precondiciones: socket != NULL && client != NULL.
 * Postcondiciones: acepta y crea un fd para el socket del cliente. Devuelve -1
 * en caso de error, 0 de lo contrario.
 */
int socket_accept(socket_t* socket, socket_t* client);

/*
 * Envía el mensaje ingresado, dado su largo, al destinatario acordado por el
 * socket dado.
 * Precondiciones: socket != NULL && msg != NULL && len > 0.
 * Postcondiciones: envía el mensaje al destinatario. Devuelve -1 en caso de
 * error, de lo contrario devuelve la cantidad de bytes enviados.
 */
int socket_send(socket_t* socket, char* msg, size_t len);

/*
 * Recibe el mensaje ingresado, y lo escribe en el buffer ingresado; siendo len
 * el largo del buffer.
 * Precondiciones: socket != NULL && msg != NULL && len > 0.
 * Postcondiciones: recibe el mensaje del destinatario y lo deja escrito en
 * el buffer ingresado. Devuelve -1 en caso de error, de lo contrario devuelve
 * la cantidad de bytes recibidos.
 */
int socket_recv(socket_t* socket, char* buf, size_t len);

#endif  // COMMON_SOCKET_H_
