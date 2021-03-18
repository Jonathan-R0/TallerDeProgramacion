// Copyright [2020]<Jonathan David Rosenblatt>
#include "client_tda.h"

#include <stdio.h>
#include <string.h>

#include "client_cipherAndSend.h"
#include "common_cesar.h"
#include "common_rc4.h"
#include "common_socket.h"
#include "common_vigenere.h"

#define CESAR_CIPHER "cesar"
#define VIGENERE_CIPHER "vigenere"
#define RC4_CIPHER "rc4"

int client_init(client_t* self) {
  if (self == NULL || socket_init(&self->mysocket) == -1) return -1;
  memset(&self->cifrado, 0, sizeof(self->cifrado));
  return 0;
}

int client_destroy(client_t* self) {
  self->destroy(&self->cifrado);
  if (self == NULL || socket_destroy(&self->mysocket) == -1) return -1;
  return 0;
}

int client_connect(client_t* self, char* port, char* ip) {
  if (self == NULL || port == NULL || ip == NULL) return -1;

  if (socket_connect(&self->mysocket, port, ip) == -1) {
    client_destroy(self);
    return -1;
  }
  return 0;
}

int client_send(client_t* self, char* msg, size_t msgLen) {
  if (self == NULL || msg == NULL) return -1;

  int bytes_sent = 0;
  while (bytes_sent < (int)msgLen) {
    if ((bytes_sent += socket_send(&self->mysocket, msg, msgLen)) == -1) {
      return -1;
    }
  }
  return 0;
}

static void _set_method(client_t* self,
                        int (*cipher_msg)(void*, unsigned char*, unsigned int),
                        void (*destroy)(void*)) {
  self->cipher_msg = cipher_msg;
  self->destroy = destroy;
}

int cipher_and_send(client_t* self, char* method, unsigned char* key) {
  if (self == NULL || method == NULL || key == NULL) return -1;
  if (strcmp(CESAR_CIPHER, method) == 0) {
    cesar_cipher_t _cesar;
    if (cesar_cipher_init(&_cesar, key) == -1) return -1;
    self->cifrado.cesar = _cesar;
    _set_method(self, &cesar_encode, &cesar_destroy);
  } else if (strcmp(VIGENERE_CIPHER, method) == 0) {
    vigenere_cipher_t _vigenere;
    if (vigenere_cipher_init(&_vigenere, key) == -1) return -1;
    self->cifrado.vigenere = _vigenere;
    _set_method(self, &vigenere_encode, &vigenere_destroy);
  } else if (strcmp(RC4_CIPHER, method) == 0) {
    rc4_cipher_t _rc4;
    if (rc4_cipher_init(&_rc4, key) == -1) return -1;
    self->cifrado.rc4 = _rc4;
    _set_method(self, &rc4_encode, &rc4_destroy);
  }
  return cipher_and_send_info(self, key);
}
