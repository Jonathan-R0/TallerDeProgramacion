#ifndef PARSER_H_
#define PARSER_H_
#include <list>
#include <string>

#include "asmline.h"

class Parser {
 public:
  Asmline parseInstruction(std::string asmLine);
};

#endif  // PARSER_H_
