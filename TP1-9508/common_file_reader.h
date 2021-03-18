// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_FILE_READER_H_
#define COMMON_FILE_READER_H_

#include <stdio.h>

/*
 * Lee al buffer ingresado lo que está en el fp dado. Lee hasta que 
 * se llena el buffer o llega al final del array. Deja un 0 en el 
 * último caracter.
 * Precondiciones: buf != NULL && fp != NULL.
 * Postcondiciones: devuelve -1 en caso de error, de lo contrario
 * devuelve la cantidad de bytes leídos. 
 */
int read_from_file_to_buf(char buf[], unsigned int msgLen, FILE* fp);

#endif  // COMMON_FILE_READER_H_
