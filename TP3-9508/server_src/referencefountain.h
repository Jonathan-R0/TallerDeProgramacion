#ifndef REFERENCEFOUNTAIN_H_
#define REFERENCEFOUNTAIN_H_

#include <iostream>
#include <map>
#include <mutex>
#include <string>

class Referencefountain {
 private:
  std::map<std::string, std::string> references;
  std::mutex m;

 public:
  std::string getReferenceFrom(const std::string& key);
  void setReferenceTo(const std::string& key, const std::string& value);
};

#endif  // REFERENCEFOUNTAIN_H_
