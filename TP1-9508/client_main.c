// Copyright [2020]<Jonathan David Rosenblatt>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_tda.h"
#include "common_arginfo.h"
#include "common_cesar.h"

#define ERR_ARG_NRO "Error, argumento inválido.\n"
#define ERR_ARG_INIT "Error al parsear info de argumento.\n"
#define CONECT_ERROR "Error de conexión con el servidor.\n"
#define INIT_ERROR "Error de inicialización del socket.\n"
#define DESTROY_ERR "Error al destruir el cliente.\n"

int main(int argc, char* argv[]) {
  if (argc != 5) {
    fprintf(stderr, ERR_ARG_NRO);
    return -1;
  }

  arginfo_t arginfo;
  client_t self;

  if (!arginfo_init(&arginfo, argc, argv)) {
    fprintf(stderr, ERR_ARG_INIT);
    return -1;
  } else if (client_init(&self) == -1) {
    fprintf(stderr, INIT_ERROR);
    return -1;
  } else if (client_connect(&self, arginfo.port, arginfo.ip) == -1) {
    fprintf(stderr, CONECT_ERROR);
    return -1;
  } else if (cipher_and_send(&self, arginfo.method,
                             (unsigned char*)arginfo.key) == -1) {
    return -1;
  } else if (client_destroy(&self) == -1) {
    fprintf(stderr, DESTROY_ERR);
    return -1;
  }
  client_destroy(&self);
  return 0;
}
