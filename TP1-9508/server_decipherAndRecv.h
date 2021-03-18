// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef SERVER_DECIPHERANDRECV_H_
#define SERVER_DECIPHERANDRECV_H_
#include "server_tda.h"

/*
 * Dado el cliente y clave recibido, desencripta con el algoritmo 
 * correspondiente todo que ingrese por red y lo escribe por stdin.
 * Precondiciones: self != NULL && socket asociado incializado y configurado
 * && key != NULL.
 * Postcondiciones: desencripta lo que recibe por red y lo escribe por stdin.
 * Devuelve  -1 en caso de error, 0 de lo contrario.
 */
int decipher_and_recv_info(server_t* self, unsigned char* key);

#endif  // SERVER_DECIPHERANDRECV_H_
