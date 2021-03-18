#include "parser.h"

#include <fstream>
#include <sstream>
#include <vector>

std::string Parser::getMethod() { return method; }
std::string Parser::getBody() { return body; }
std::string Parser::getResource() { return resource; }
std::string Parser::getRoot() { return root; }

void Parser::operator()(std::string& alllines) {
  std::string line;
  std::stringstream lines(alllines);

  lines >> method;
  lines >> resource;
  lines >> protocol;
  resource.erase(0, 1);

  std::string exitmsg = method + " /" + resource + " " + protocol + "\n";
  std::cout << exitmsg;

  bool isBody = false;
  getline(lines, line);  // La primera siempre me queda vacía.
  while (getline(lines, line)) {
    if (line.empty()) isBody = true;
    if (isBody && !line.empty()) body += "\n" + line;
  }
}

Parser::Parser(const std::string& filename) { fillroot(filename); }

void Parser::fillroot(const std::string& filename) {
  std::ifstream file;
  std::string line;
  file.open(filename);
  while (getline(file, line)) {
    root += "\n" + line;
  }
}
