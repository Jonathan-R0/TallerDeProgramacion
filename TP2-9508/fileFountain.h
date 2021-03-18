#ifndef FILEFOUNTAIN_H_
#define FILEFOUNTAIN_H_

#include <mutex>
#include <string>
#include <vector>

class FileFountain {
 private:
  std::vector<std::string> files;
  std::mutex m;

 public:
  FileFountain(int argc, char *argv[]);
  std::string getNext();
};

#endif  // FILEFOUNTAIN_H_
