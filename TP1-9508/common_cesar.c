// Copyright [2020]<Jonathan David Rosenblatt>
#include "common_cesar.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ENCODE 1
#define DECODE -1

int cesar_cipher_init(void* cipher, unsigned char* key) {
  if (cipher == NULL) return -1;
  cipher = (cesar_cipher_t*)cipher;
  ((cesar_cipher_t*)cipher)->shift = (unsigned int)strtol((char*)key, NULL, 10);
  return 0;
}

int cesar_shift_bytes(cesar_cipher_t* cesar, unsigned char msg[],
                      unsigned int msgLen, int incremento) {
  int shift = cesar->shift * incremento;
  if (msg == NULL) return -1;
  for (int i = 0; i < msgLen; i++) {
    unsigned int caracter = msg[i];
    msg[i] = (caracter + shift) % 256;
  }
  return 0;
}

int cesar_encode(void* cipher, unsigned char msg[], unsigned int msgLen) {
  if (cipher == NULL || msg == NULL) return -1;
  return cesar_shift_bytes((cesar_cipher_t*)cipher, msg, msgLen, ENCODE);
}

int cesar_decode(void* cipher, unsigned char msg[], unsigned int msgLen) {
  if (cipher == NULL || msg == NULL) return -1;
  return cesar_shift_bytes((cesar_cipher_t*)cipher, msg, msgLen, DECODE);
}

void cesar_destroy(void* cipher) {}
