// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef CLIENT_TDA_H_
#define CLIENT_TDA_H_

#include "common_cipher.h"
#include "common_socket.h"

typedef struct client {
  socket_t mysocket;
  int (*cipher_msg)(void*, unsigned char*, unsigned int);
  void (*destroy)(void*);
  generico_t cifrado;
} client_t;

/*
 * Inicializa el tda client, su correspondiente socket asociado y deja en ceros
 * el espacio correspondiente al cifrado genérico.
 * Precondiciones: self != NULL.
 * Postcondiciones: deja el socket asociado inicializado. Devuelve
 * -1 en caso de error, 0 de lo contrario.
 */
int client_init(client_t* self);

/*
 * Destruye el elemento ingresado así como a sus atributos asociados.
 * Precondiciones: self != NULL.
 * Postcondiciones: libera los recursos que haya usado el elemento. Devuelve -1
 * en caso de error, 0 de lo contrario.
 */
int client_destroy(client_t* self);

/*
 * Intenta establecer una conexión con el puerto e ip dados. Si el bind,
 * listen o accept fallan, se liberan los recursos.
 * Precondiciones: self != NULL && port != NULL && ip != NULL.
 * Postcondiciones: deja los sockets inicializados para enviar y recibir datos
 * entre el cliente y servidor. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int client_connect(client_t* self, char* port, char* ip);

/*
 * Dado el cliente y mensaje dados, con su largo correspondiente, envia la
 * cantidad de caracteres del mismo indicados por el socket asociado al
 * cliente.
 * Precondiciones: self != NULL && self inicializado y configurado
 * && msg != NULL
 * Postcondiciones: envía el mensaje recibido por el socket asociado. Devuelve
 * -1 en caso de error, 0 de lo contrario.
 */
int client_send(client_t* self, char* msg, size_t msgLen);

/*
 * Dado el cliente, el método a utilizar y la llave elegida, inicializa el 
 * cipher correspondiente dentro de la estructura cliente y termina llamando
 * a las otras funciones que desencadenan la lectura, cifrado y enviado de 
 * la información.
 * Precondiciones: self != NULL && method != NULL && key != NULL.
 * Postcondiciones: completa el enviado de la información, llamando al
 * destructor del cliente al concluir. Devuelve -1 en caso de error, 0 de
 * lo contrario.
 */ 
int cipher_and_send(client_t* self, char* method, unsigned char* key);

#endif  // CLIENT_TDA_H_
