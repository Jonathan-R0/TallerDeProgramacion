// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_CESAR_H_
#define COMMON_CESAR_H_

typedef struct cesar_cipher {
  int shift;
} cesar_cipher_t;

/*
 * Inicializa el cipher recibido con la key, es decir, con el valor númerico que
 * representa la cantidad de bytes a shiftear cada char del mensaje.
 * Precondiciones: cipher != NULL.
 * Postcondiciones: deja el cipher inicializado. Devuelve -1 en caso de error, 0
 * de lo contrario.
 */
int cesar_cipher_init(void* cipher, unsigned char* key);

/*
 * Dado un mensaje se codifica en función del incremento de caracteres indicado
 * por el cipher.
 * Precondición: string != NULL && cipher inicializado && cipher != NULL.
 * Postcondiciones: deja el mensaje cifrado en el mismo array que
 * ingresa. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int cesar_encode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Dado un mensaje se decodifica en función del decremento de caracteres
 * indicado por el cipher.
 * Precondición: string != NULL && cipher inicializado && cipher != NULL.
 * Postcondiciones: deja el mensaje descifrado en el mismo
 * array que ingresa. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int cesar_decode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Dado un mensaje se codifica o decodifica, en función del incremento o
 * decremento a computar en los caracteres.
 * Precondición: msg != NULL.
 * Postcondiciones: deja el mensaje cifrado o descifrado en el mismo array que
 * ingresa. Devuelve -1 en caso de error, 0 de lo contrario.
 */
int cesar_shift_bytes(cesar_cipher_t* cesar, unsigned char msg[],
                      unsigned int msgLen, int incremento);

/*
 * Destruye el cipher recibido, liberando todos los recursos que este pueda
 * estar usando.
 * Postcondiciones: libera todos los recursos.
 */
void cesar_destroy(void* cipher);

#endif  // COMMON_CESAR_H_
