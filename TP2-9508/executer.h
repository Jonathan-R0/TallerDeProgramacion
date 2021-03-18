#ifndef EXECUTER_H_
#define EXECUTER_H_

#include <vector>

#include "eBPF.h"

class Executer {
 private:
  int numberOfThreads;
  std::vector<EBPF*> holders;

 public:
  explicit Executer(char* argv[])
      : numberOfThreads(strtol(argv[1], NULL, 10)) {}
  void run(int argc, char* argv[]);
};

#endif  // EXECUTER_H_
