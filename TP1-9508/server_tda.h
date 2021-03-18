// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_SERVER_TDA_H_
#define COMMON_SERVER_TDA_H_

#include "common_cipher.h"
#include "common_socket.h"

typedef struct server {
  socket_t mysocket;
  socket_t client;
  int (*decipher_msg)(void*, unsigned char*, unsigned int);
  void (*destroy)(void*);
  generico_t descifrado;
} server_t;

/*
 * Inicializa el tda server y sus correspondientes sockets asociados.
 * Precondiciones: self != NULL.
 * Postcondiciones: deja los sockets asociados inicializados. Devuelve
 * -1 en caso de error, 0 de lo contrario.
 */
int server_init(server_t* self);

/*
 * Destruye el elemento ingresado así como a sus atributos asociados.
 * Precondiciones: self != NULL.
 * Postcondiciones: libera los recursos que haya usado el elemento. Devuelve -1
 * en caso de error, 0 de lo contrario.
 */
int server_destroy(server_t* self);

/*
 * Intenta establecer una conexión con el puerto dado. Si el bind, listen o
 * accept fallan, se liberan los recursos.
 * Precondiciones: self != NULL && port != NULL.
 * Postcondiciones: deja los sockets inicializados para enviar y recibir datos
 * entre el cliente y servidor. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int server_accept(server_t* self, char* port);

/*
 * Dado el cliente y mensaje dados, con su largo correspondiente, recibe la
 * cantidad de caracteres del mismo indicados por el socket asociado al
 * cliente.
 * Precondiciones: self != NULL && self inicializado y configurado
 * && buf != NULL
 * Postcondiciones: recibe el mensaje enviado por el socket asociado.
 * Devuelve -1 en caso de error, la cantidad de chars leidos de lo contrario.
 */
int server_recv(server_t* self, char buf[], int bufLen);

/*
 * En función del servidor, método y clave dados, desencripta el mensaje
 * que va llegando por red y lo escribe a stdout.
 * Precondiciones: self != NULL && method != NULL & key != NULL.
 * Postcondiciones: lee todo lo que ingresa por red y lo escribe a stdout en
 * función del método y clave. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int decipher_and_recv(server_t* self, char* method, unsigned char* key);
#endif  // COMMON_SERVER_TDA_H_
