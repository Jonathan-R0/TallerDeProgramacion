#include "invalidanswer.h"

#include "parser.h"
#include "referencefountain.h"

#define INVALID_ERROR_START "HTTP/1.1 405 METHOD NOT ALLOWED\n\n"
#define INVALID_ERROR_END " es un comando desconocido"

std::string InvalidAnswer::generate(Parser& parser, Referencefountain& msg) {
  return INVALID_ERROR_START + parser.getMethod() + INVALID_ERROR_END;
}
