#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <string>

#include "parser.h"
#include "referencefountain.h"

class Response {
 public:
  static Response* create(Parser& parser);
  virtual ~Response() = 0;
  virtual std::string generate(Parser& parser, Referencefountain& msg) = 0;
};

#endif  // RESPONSE_H_
