#include "postanswer.h"

#include "parser.h"
#include "referencefountain.h"

#define OK_POSTANSWER "HTTP/1.1 200 OK\n"
#define ERROR_POSTANSWER "HTTP/1.1 403 FORBIDDEN\n"

std::string PostAnswer::generate(Parser& parser, Referencefountain& msg) {
  if (!parser.getResource().empty()) {
    msg.setReferenceTo(parser.getResource(), parser.getBody());
    return OK_POSTANSWER + parser.getBody();
  }
  return ERROR_POSTANSWER;
}
