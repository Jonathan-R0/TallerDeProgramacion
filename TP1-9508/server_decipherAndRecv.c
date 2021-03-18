// Copyright [2020]<Jonathan David Rosenblatt>
#include "server_decipherAndRecv.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_cesar.h"
#include "common_file_reader.h"
#include "common_rc4.h"
#include "common_vigenere.h"
#include "server_tda.h"

#define BYTES_A_ESCRIBIR 65

int decipher_and_recv_info(server_t* self, unsigned char* key) {
  if (self == NULL || key == NULL) return -1;
  unsigned char msg[BYTES_A_ESCRIBIR];
  int read = -1;
  while ((read = server_recv(self, (char*)msg, BYTES_A_ESCRIBIR - 1)) != 0) {
    if (read == -1 || self->decipher_msg(&self->descifrado, msg, read) == -1) {
      fprintf(stderr, "%s\n", strerror(errno));
      return -1;
    }
    printf("%s", msg);
  }
  return 0;
}
