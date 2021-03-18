// Copyright [2020]<Jonathan David Rosenblatt>
#include "common_arginfo.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#define ERR_OVERFLOW \
  "Error, el método de encriptación y/o llave son demasiado largos.\n"
#define ERR_INV_TYPE "Error, opcion pasada por argumento no válida.\n"
#define METODO_DE_ENCRIPTACION "method="
#define LLAVE_DE_ENCRIPTACION "key="

static int metodoEsValido(char* metodo) {
  if (strcmp(metodo, "rc4") == 0 || strcmp(metodo, "cesar") == 0 ||
      strcmp(metodo, "vigenere") == 0) {
    return 1;
  }
  return 0;
}

void getPortAndIp(arginfo_t* info, int argc, char* argv[]) {
  memset(info->ip, 0, sizeof(info->ip));
  memset(info->port, 0, sizeof(info->port));
  if (info == NULL || argv == NULL) {
    return;
  } else if (argc == 4) {
    strncpy(info->port, argv[3], sizeof(info->port));
    *(info->ip) = '\0';
  } else if (argc == 5) {
    strncpy(info->ip, argv[3], sizeof(info->ip));
    strncpy(info->port, argv[4], sizeof(info->port));
  }
}

int getMethodAndKey(arginfo_t* info, const struct option validArgs[], int argc,
                    char* argv[]) {
  int opt;
  int hayLlave = 0;
  int hayMetodo = 0;
  while ((opt = getopt_long(argc, argv, "mk", validArgs, NULL)) != -1) {
    if (sizeof(optarg) >= SIZE_OF_STRINGS) {
      fprintf(stderr, ERR_OVERFLOW);
      return 0;
    }
    switch (opt) {
      case ('m'):
        strncpy(info->method, optarg, strlen(optarg) + 1);
        hayMetodo++;
        continue;
      case ('k'):
        strncpy(info->key, optarg, strlen(optarg) + 1);
        hayLlave++;
        continue;
      default:
        fprintf(stderr, ERR_INV_TYPE);
        return 0;
    }
  }
  if (!metodoEsValido(info->method)) return 0;
  return (hayLlave && hayMetodo);  // Esperamos que tenga llave y método.
}

int arginfo_init(arginfo_t* info, int argc, char* argv[]) {
  struct option validArgs[3];
  const struct option method = {
      .name = METODO_DE_ENCRIPTACION, .has_arg = required_argument, .val = 'm'};
  const struct option key = {
      .name = LLAVE_DE_ENCRIPTACION, .has_arg = required_argument, .val = 'k'};
  const struct option final = {.name = 0, .has_arg = 0, .val = 0};
  validArgs[0] = method;
  validArgs[1] = key;
  validArgs[2] = final;

  int validez = getMethodAndKey(info, validArgs, argc, argv);
  getPortAndIp(info, argc, argv);

  return (validez);
}
