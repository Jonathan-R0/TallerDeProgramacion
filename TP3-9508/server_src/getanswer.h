#ifndef GETANSWER_H_
#define GETANWSER_H_

#include <string>

#include "parser.h"
#include "referencefountain.h"
#include "response.h"

class GetAnswer : public Response {
 public:
  std::string generate(Parser& parser, Referencefountain& msg) override;
};

#endif  // GETANSWER_H_
