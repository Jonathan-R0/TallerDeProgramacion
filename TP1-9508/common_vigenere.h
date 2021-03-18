// Copyright [2020]<Jonathan David Rosenblatt>
#ifndef COMMON_VIGENERE_H_
#define COMMON_VIGENERE_H_

typedef struct vigenere_cipher {
  unsigned char* key;
  unsigned int
      lastKeyIndex;  // Me guardo la última posición de la clave que usé.
} vigenere_cipher_t;

/*
 * Inicializa el cipher dada una key válida. También guardará la última posición
 * de la key por la que pasó por si tuviera que cortar el proceso de codificado
 * a la mitad.
 * Precondiciones: cipher != NULL && key != NULL.
 * Postcondiciones: deja el cipher recibido inicializado. Se devuelve -1 si
 * ocurre un error, 0 de lo contrario.
 */
int vigenere_cipher_init(void* cipher, unsigned char* key);

/*
 * Dado un cipher válido, un mensaje y su largo se codifica o descodifica el
 * mismo. Se sumarán bytes al codificar y restarán al decodificar en función de
 * si estoyCifrando es 1 o -1, respectivamente. Precondiciones: cipher != NULL
 * && cipher inicializado && string != NULL && estoyCifrando = 1 o -1
 * Postcondiciones: se sobreescribirá el mensaje con su versión cifrada. Se
 * devuelve -1 si ocurre un error, 0 de * lo contrario.
 */
int vigenere_cipher_shift_bytes(vigenere_cipher_t* cipher, int estoyCifrando,
                                unsigned char msg[], unsigned int msgLen);

/*
 * Dado un cipher válido y un mensaje se codifica el mismo.
 * Precondiciones: cipher != NULL && cipher inicializado && string != NULL
 * Postcondiciones: se sobreescribirá el mensaje con su versión cifrada. Se
 * devuelve -1 si ocurre un error, 0 de * lo contrario.
 */
int vigenere_encode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Dado un cipher válido, un mensaje y el largo del mismo se decodifica el
 * mismo.
 * Precondiciones: cipher != NULL&& cipher inicializado  && string != NULL
 * Postcondiciones: se sobreescribirá el mensaje con su versión descifrada.
 * Se devuelve -1 si ocurre un error, 0 de * lo contrario.
 */
int vigenere_decode(void* cipher, unsigned char msg[], unsigned int msgLen);

/*
 * Destruye el cipher recibido, liberando todos los recursos que este pueda
 * estar usando.
 * Postcondiciones: libera todos los recursos asociados.
 */
void vigenere_destroy(void* cipher);

#endif  // COMMON_VIGENERE_H_
