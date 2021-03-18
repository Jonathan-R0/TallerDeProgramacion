#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>

class Parser {
 private:
  void fillroot(const std::string& rootfile);
  std::string method;
  std::string resource;
  std::string protocol;
  std::string body;
  std::string root;

 public:
  std::string getMethod();
  std::string getBody();
  std::string getResource();
  std::string getRoot();

  explicit Parser(const std::string& file);
  void operator()(std::string& alllines);
};

#endif  // PARSER_H_
