#include "parser.h"

#include <iostream>
#include <string>
#include <utility>

static void parseSpaces(std::string* asmLine) {
  std::string noSpacesExtra = {};
  char anterior = 0;
  for (auto c : *asmLine) {
    if (!(c == ' ' && anterior == ' ')) noSpacesExtra.push_back(c);
    anterior = c;
  }
  if (noSpacesExtra.front() == ' ') noSpacesExtra.erase(0, 1);
  *asmLine = noSpacesExtra;
}

static std::string makeLabel(int firstDots, std::string* asmLine) {
  if (firstDots == -1) return "";
  std::string label = asmLine->substr(0, firstDots);
  asmLine->erase(0, firstDots + 1);
  asmLine->erase(0, asmLine->find_first_not_of(" "));
  return label;
}

static std::string makeOpCode(int firstSpace, std::string* asmLine) {
  if (firstSpace == -1) return "";
  std::string opCode = asmLine->substr(0, firstSpace);
  asmLine->erase(0, firstSpace + 1);
  return opCode;
}

Asmline Parser::parseInstruction(std::string asmLine) {
  parseSpaces(&asmLine);
  std::string label(makeLabel(asmLine.find_first_of(":"), &asmLine));
  std::string opCode(makeOpCode(asmLine.find_first_of(" "), &asmLine));

  Asmline instruction(std::move(label), std::move(opCode));

  if (instruction.isJump()) {
    int firstComma = asmLine.find_first_of(",");
    if (firstComma != -1) {
      asmLine.erase(0, firstComma + 2);
      int secondComma = asmLine.find_first_of(",");
      if (secondComma != -1) {
        instruction.setLabelToJump(asmLine.substr(0, secondComma));
        asmLine.erase(0, secondComma + 2);
      }
      instruction.setLabelToJump(asmLine);
    } else {
      instruction.setLabelToJump(asmLine);
    }
  }
  return instruction;
}
