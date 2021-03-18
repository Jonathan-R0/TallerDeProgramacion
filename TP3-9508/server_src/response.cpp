#include "response.h"

#include <iostream>

#include "getanswer.h"
#include "invalidanswer.h"
#include "parser.h"
#include "postanswer.h"

#define GET_METHOD "GET"
#define POST_METHOD "POST"

Response::~Response() {}

Response* Response::create(Parser& parser) {
  if (parser.getMethod() == GET_METHOD) {
    return new GetAnswer();
  } else if (parser.getMethod() == POST_METHOD) {
    return new PostAnswer();
  }
  return new InvalidAnswer();
}
