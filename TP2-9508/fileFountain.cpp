#include "fileFountain.h"

#include <algorithm>
#include <iostream>
#include <mutex>
#include <utility>

FileFountain::FileFountain(int argc, char* argv[]) {
  for (int i = argc - 1; i > 1; i--) {
    files.push_back(std::string(argv[i]));
  }
}

std::string FileFountain::getNext() {
  std::unique_lock<std::mutex> lock(m);
  if (files.size() == 0) return "";
  std::string file(std::move(files.back()));
  files.pop_back();
  return file;
}
