// Copyright [2020]<Jonathan David Rosenblatt>
#include "common_rc4.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

/*
 * Swappea los elementos de la posición "coef1" y "coef2" dentro del arreglo
 * recibido. Precondiciones: s != NULL && coef1,coef2 < strlen(s)
 * Postcondiciones: swappea los elementos, si el arreglo ingresado es NULL no
 * hace nada.
 */
static void _swap_chars(unsigned char* s, unsigned int coef1,
                        unsigned int coef2) {
  if (s == NULL) return;
  unsigned char temp = s[coef1];
  s[coef1] = s[coef2];
  s[coef2] = temp;
}

int rc4_cipher_init(void* cipher, unsigned char* key) {
  if (cipher == NULL || key == NULL) return -1;
  ((rc4_cipher_t*)cipher)->coefi = ((rc4_cipher_t*)cipher)->coefj = 0;
  unsigned int len = (unsigned int)strlen((char*)key);

  unsigned int i, j;
  for (i = 0; i < 256; i++) ((rc4_cipher_t*)cipher)->S[i] = (char)i;

  for (i = j = 0; i < 256; i++) {
    j = (j + key[i % len] + ((rc4_cipher_t*)cipher)->S[i]) & 255;
    _swap_chars(((rc4_cipher_t*)cipher)->S, i, j);
  }

  return 0;
}

unsigned char randChar(rc4_cipher_t* cipher) {
  if (cipher == NULL) return -1;

  unsigned int i = cipher->coefi;  // Con estas variables evitamos
  unsigned int j = cipher->coefj;  // tantos accesos a memoria.

  i = (i + 1) & 255;
  j = (j + cipher->S[i]) & 255;

  _swap_chars(cipher->S, i, j);

  cipher->coefi = i;
  cipher->coefj = j;

  return cipher->S[(cipher->S[i] + cipher->S[j]) & 255];
}

int rc4_encode(void* cipher, unsigned char msg[], unsigned int len) {
  // Es necesario reiniciar el cipher para desencriptar.
  if (cipher == NULL || msg == NULL) return -1;
  return rc4_decode((rc4_cipher_t*)cipher, msg, len);
}

int rc4_decode(void* cipher, unsigned char msg[], unsigned int len) {
  if (cipher == NULL || msg == NULL) return -1;

  for (int k = 0; k < len; k++) {
    msg[k] ^= randChar((rc4_cipher_t*)cipher);
  }

  return 0;
}

void rc4_destroy(void* cipher) {}
