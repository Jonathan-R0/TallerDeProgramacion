#include "referencefountain.h"

std::string Referencefountain::getReferenceFrom(const std::string& key) {
  std::unique_lock<std::mutex> lock(m);
  return references.at(key);
}

void Referencefountain::setReferenceTo(const std::string& key,
                                       const std::string& value) {
  std::unique_lock<std::mutex> lock(m);
  references[key] = value;
}
