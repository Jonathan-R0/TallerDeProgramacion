#ifndef GRAPHFILLER_H_
#define GRAPHFILLER_H_

#include <list>
#include <map>
#include <string>

#include "graph.h"
#include "parser.h"

class Graphfiller {
 private:
  std::map<std::string, std::list<int>> referenciasColgadas;
  std::map<std::string, int> referenciasReconocidas;
  std::list<int> aristaACortar;
  Parser parser;
  Graph opGraph;

 public:
  void restart();
  void connectLostTags();
  void addInstructionToGraph(std::string line, int lineNumber);
  bool hasCycle();
  bool hasUnusedInstruction();
};

#endif  // GRAPHFILLER_H_
