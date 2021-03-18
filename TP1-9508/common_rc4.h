// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_RC4_H_
#define COMMON_RC4_H_

/*
 * Las variables 'S', 'a' y 'b' existen para que el struct pueda generar el
 * valor con el que se hace el XOR al mensaje entrante. Estos deben existir en
 * el struct ya que la encriptación correcta cada mensaje depende de que se
 * guarde el estado de estas variables de iteraciones anteriores.
 */
typedef struct rc4_cipher {
  unsigned char S[256];
  unsigned int coefi;
  unsigned int coefj;
} rc4_cipher_t;

/*
 * Inicializa el cipher dada la key ingresada.
 * Precondiciones: cipher != NULL && key != NULL
 * Postcondiciones: deja el cipher inicializado. Devuevle -1 en caso de error, 0
 * de lo contrario.
 */
int rc4_cipher_init(void* cipher, unsigned char* key);

/*
 * Codifica el mensaje ingresado en función el cipher dado.
 * Precondiciones: cipher != NULL && ciper inicializado && string != NULL.
 * Postcondiciones: deja el mensaje codificado en el array ingresado. Devuelve
 * -1 en caso de error, 0 de lo contrario
 */
int rc4_encode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Decodifica el mensaje ingresado en función el cipher dado.
 * Precondiciones: cipher != NULL && cipher inicializado && string != NULL.
 * Postcondiciones: deja el mensaje decodificado en el array ingresado. Devuelve
 * -1 en caso de error, 0 de lo contrario.
 */
int rc4_decode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Destruye el cipher recibido, liberando todos los recursos que este pueda
 * estar usando.
 * Postcondiciones: libera todos los recursos asociados. 
 */
void rc4_destroy(void* cipher);

/*
 * Devuelve un char cuyo valor numérico está generado en función del estado del
 * cipher que ingrese.
 * Precondiciones: cipher != NULL && cipher inicializado.
 * Postcondiciones: devuelve el char generado.
 */
unsigned char randChar(rc4_cipher_t* cipher);

#endif  // COMMON_RC4_H_
