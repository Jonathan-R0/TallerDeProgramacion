// Copyright [2020]<Jonathan David Rosenblatt>
#include "client_cipherAndSend.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_tda.h"
#include "common_cesar.h"
#include "common_file_reader.h"
#include "common_rc4.h"
#include "common_vigenere.h"

#define ARCHIVO_A_LEER stdin
#define BYTES_A_LEER 64

int cipher_and_send_info(client_t* self, unsigned char* key) {
  if (self == NULL || key == NULL) return -1;
  unsigned char msg[BYTES_A_LEER];
  int read = -1;
  while ((read = read_from_file_to_buf((char*)msg, BYTES_A_LEER,
                                       ARCHIVO_A_LEER)) != 0) {
    if (read == -1 || self->cipher_msg(&self->cifrado, msg, read) == -1 ||
        client_send(self, (char*)msg, read) == -1) {
      fprintf(stderr, "%s\n", strerror(errno));
      return -1;
    }
  }
  return 0;
}
