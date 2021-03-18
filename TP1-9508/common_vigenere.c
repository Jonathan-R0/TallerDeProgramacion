// Copyright [2020]<Jonathan David Rosenblatt>
#include "common_vigenere.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vigenere_shift_bytes(vigenere_cipher_t* cipher, int estoyCifrando,
                         unsigned char msg[], unsigned int msgLen) {
  unsigned int keyLen = (unsigned int)strlen((char*)cipher->key);
  if (msg == NULL && !(estoyCifrando == -1 || estoyCifrando == 1)) return -1;
  unsigned char buf[msgLen];
  int i;
  int j = cipher->lastKeyIndex;
  for (i = 0; i < msgLen; i++) {
    unsigned int suma =
        msg[i % msgLen] + estoyCifrando * cipher->key[j % keyLen];
    buf[i] = suma % 256;
    j++;
  }
  strncpy((char*)msg, (char*)buf, msgLen);
  cipher->lastKeyIndex = j;
  return 0;
}

int vigenere_encode(void* cipher, unsigned char msg[], unsigned int msgLen) {
  if (cipher == NULL) return -1;
  return vigenere_shift_bytes(((vigenere_cipher_t*)cipher), 1, msg, msgLen);
}

int vigenere_decode(void* cipher, unsigned char msg[], unsigned int msgLen) {
  // Es necesario desencriptar con un cipher diferente al que se usó para
  // encriptar.
  if (cipher == NULL || msg == NULL) return -1;
  return vigenere_shift_bytes(((vigenere_cipher_t*)cipher), -1, msg, msgLen);
}

int vigenere_cipher_init(void* cipher, unsigned char* key) {
  if (cipher == NULL || key == NULL) return -1;
  ((vigenere_cipher_t*)cipher)->key = key;
  ((vigenere_cipher_t*)cipher)->lastKeyIndex = 0;
  return 0;
}

void vigenere_destroy(void* cipher) {}
