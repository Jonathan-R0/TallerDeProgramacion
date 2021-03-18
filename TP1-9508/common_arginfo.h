// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_ARGINFO_H_
#define COMMON_ARGINFO_H_

#include <getopt.h>
#define SIZE_OF_STRINGS 32
#define SIZE_OF_METHOD SIZE_OF_STRINGS
#define SIZE_OF_KEY SIZE_OF_STRINGS
#define SIZE_OF_PORT SIZE_OF_STRINGS
#define SIZE_OF_IP SIZE_OF_STRINGS


typedef struct arginfo {
  char method[SIZE_OF_METHOD];
  char key[SIZE_OF_KEY];
  char port[SIZE_OF_PORT];
  char ip[SIZE_OF_IP];
} arginfo_t;

/*
 * Dado un struct arginfo y los datos recibidos por argumento, inicializa el
 * mismo asignandole los datos correspondientes.
 * Precondiciones: info != NULL && argc == 4 o 5 && argv != NULL.
 * Postcondiciones: deja el struct inicializado en función de los datos
 * ingresados. Devuelve 0 en caso de error, 1 de lo contrario.
 */
int arginfo_init(arginfo_t* info, int argc, char* argv[]);

/*
 * Dado un struct arginfo y los datos recibidos por argumento, les asigna la ip
 * y puerto al mismo.
 * Precondiciones: info != NULL && argc == 4 o 5  && argv != NULL.
 * Postcondiciones: deja los campos de ip y puertos inicializados. Si no le
 * corresponde tener una ip por ser cliente, se dejará el primer byte con un 0.
 */
void getPortAndIp(arginfo_t* info, int argc, char* argv[]);

/*
 * Dado un struct arginfo, los datos recibidos por argumento y un struct opcion
 * que representa las opciones válidas, les asigna el método de encriptación y
 * key al mismo.
 * Precondiciones: info != NULL && validArgs != NULL  && argv != NULL.
 * Postcondiciones: deja los campos de method y key inicializados. Si todo
 * sale bien las variables "hayMetodo" y "hayLlave" serán 1, y se devolverá un
 * AND entre estos dos para verificar que ninguno es cero. Devuelve 0 en caso
 * de error.
 */
int getMethodAndKey(arginfo_t* info, const struct option validArgs[], int argc,
                    char* argv[]);

#endif  // COMMON_ARGINFO_H_
