#include "getanswer.h"

#include "parser.h"
#include "referencefountain.h"

#define OK_HTMLCODE "HTTP/1.1 200 OK\n\n"
#define GET_ERROR "HTTP 404 NOT FOUND\n\n"
#define OK_ROOTFILE "HTTP/1.1 200 OK\nContent-Type: text/html\n"

std::string GetAnswer::generate(Parser& parser, Referencefountain& msg) {
  if (!parser.getResource().empty()) {
    std::string htmlcode = msg.getReferenceFrom(parser.getResource());
    if (htmlcode != "") {
      return OK_HTMLCODE + htmlcode;
    } else {
      return GET_ERROR;
    }
  }
  return OK_ROOTFILE + parser.getRoot();
}
