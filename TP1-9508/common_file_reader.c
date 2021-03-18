// Copyright [2020]<Jonathan David Rosenblatt>
#include "common_file_reader.h"

#include <stdio.h>

int read_from_file_to_buf(char buf[], unsigned int msgLen, FILE* fp) {
  if (buf == NULL || fp == NULL) return -1;
  unsigned int porLeer = msgLen;
  unsigned int leidos = 0;
  while (!feof(fp) && porLeer != 0) {
    leidos += fread(buf + leidos, 1, msgLen, fp);
    porLeer -= leidos;
  }
  return leidos;
}
