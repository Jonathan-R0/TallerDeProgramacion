#include "asmline.h"

#include <algorithm>
#include <iostream>
#include <utility>

Asmline::Asmline(const std::string& label_, const std::string& opCode_)
    : opCode(opCode_),
      label(label_),
      jumpCodes({"jmp", "ja", "jeq", "jneq", "jne", "jlt", "jle", "jgt", "jge",
                 "jset"}) {}

bool Asmline::isJump() {
  return (find(jumpCodes.begin(), jumpCodes.end(), opCode) != jumpCodes.end());
}

bool Asmline::esCortante() {
  return (opCode == "ret" || opCode == "jmp" ||
      (this->isJump() && labelsToJump.size() == 2));
}

std::string Asmline::getLabel() { return this->label; }
std::list<std::string> Asmline::getLabelsToJumpTo() {
  return this->labelsToJump;
}
void Asmline::setLabelToJump(std::string labelToJumpGiven) {
  labelsToJump.push_back(labelToJumpGiven);
}

Asmline::Asmline(Asmline&& other) {
  this->opCode = std::move(other.opCode);
  this->label = std::move(other.label);
  this->labelsToJump = std::move(other.labelsToJump);
  this->jumpCodes = std::move(other.jumpCodes);
}
