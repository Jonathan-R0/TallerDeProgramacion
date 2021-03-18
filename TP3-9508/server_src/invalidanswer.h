#ifndef INVALIDANSWER_H_
#define INVALIDANWSER_H_

#include <string>

#include "parser.h"
#include "referencefountain.h"
#include "response.h"

class InvalidAnswer : public Response {
 public:
  std::string generate(Parser& parser, Referencefountain& msg) override;
};

#endif  // INVALIDANSWER_H_
