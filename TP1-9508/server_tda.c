// Copyright [2020]<Jonathan David Rosenblatt>
#include "server_tda.h"

#include <stdio.h>
#include <string.h>

#include "common_cesar.h"
#include "common_rc4.h"
#include "common_socket.h"
#include "common_vigenere.h"
#include "server_decipherAndRecv.h"

#define CESAR_CIPHER "cesar"
#define VIGENERE_CIPHER "vigenere"
#define RC4_CIPHER "rc4"
#define QUEUE_SIZE 10

int server_init(server_t* self) {
  if (self == NULL || socket_init(&self->mysocket) == -1 ||
      socket_init(&self->client) == -1)
    return -1;
  memset(&self->descifrado, 0, sizeof(self->descifrado));
  return 0;
}

int server_destroy(server_t* self) {
  self->destroy(&self->descifrado);
  if (self == NULL || socket_destroy(&self->mysocket) == -1 ||
      socket_destroy(&self->client) == -1)
    return -1;
  return 0;
}

int server_accept(server_t* self, char* port) {
  if (self == NULL || port == NULL) return -1;

  if (socket_bind(&self->mysocket, port) == -1 ||
      socket_listen(&self->mysocket, QUEUE_SIZE) == -1 ||
      socket_accept(&self->mysocket, &self->client) == -1) {
    server_destroy(self);
    return -1;
  }
  return 0;
}

int server_recv(server_t* self, char buf[], int bufLen) {
  int bytes_read = -1;
  while (bytes_read < 0) {
    if ((bytes_read = socket_recv(&self->client, buf, bufLen)) == -1) {
      return -1;
    }
    buf[bytes_read] = 0;
  }
  return bytes_read;
}

static void _set_method(server_t* self,
                        int (*decipher_msg)(void*, unsigned char*,
                                            unsigned int),
                        void (*destroy)(void*)) {
  self->decipher_msg = decipher_msg;
  self->destroy = destroy;
}

int decipher_and_recv(server_t* self, char* method, unsigned char* key) {
  if (self == NULL || method == NULL || key == NULL) return -1;
  if (strcmp(CESAR_CIPHER, method) == 0) {
    cesar_cipher_t _cesar;
    if (cesar_cipher_init(&_cesar, key) == -1) return -1;
    self->descifrado.cesar = _cesar;
    _set_method(self, &cesar_decode, &cesar_destroy);
  } else if (strcmp(VIGENERE_CIPHER, method) == 0) {
    vigenere_cipher_t _vigenere;
    if (vigenere_cipher_init(&_vigenere, key) == -1) return -1;
    self->descifrado.vigenere = _vigenere;
    _set_method(self, &vigenere_decode, &vigenere_destroy);
  } else if (strcmp(RC4_CIPHER, method) == 0) {
    rc4_cipher_t _rc4;
    if (rc4_cipher_init(&_rc4, key) == -1) return -1;
    self->descifrado.rc4 = _rc4;
    _set_method(self, &rc4_decode, &rc4_destroy);
  }
  return decipher_and_recv_info(self, key);
}

