// Copyright [2020]<Jonathan David Rosenblatt>
#include <stdio.h>
#include <string.h>

#include "common_arginfo.h"
#include "common_socket.h"
#include "server_decipherAndRecv.h"
#include "server_tda.h"

#define BUF_SIZE 65
#define ERR_ARG_NRO "Error, argumento inválido.\n"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, ERR_ARG_NRO);
    return 1;
  }

  arginfo_t arginfo;
  server_t self;

  if (!arginfo_init(&arginfo, argc, argv)) {
    return 1;
  } else if (server_init(&self) == -1) {
    return 1;
  } else if (server_accept(&self, arginfo.port) == -1) {
    return 1;
  } else if (decipher_and_recv(&self, arginfo.method,
                               (unsigned char*)arginfo.key) == -1) {
    return 1;
  } else if (server_destroy(&self) == -1) {
    return 1;
  }
  return 0;
}
