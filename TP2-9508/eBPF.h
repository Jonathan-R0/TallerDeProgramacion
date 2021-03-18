#ifndef EBPF_H_
#define EBPF_H_

#include <list>
#include <map>
#include <mutex>
#include <string>

#include "fileFountain.h"
#include "graph.h"
#include "graphFiller.h"
#include "parser.h"
#include "results.h"
#include "thread.h"

class EBPF : public Thread {
 private:
  Results& results;
  FileFountain& fileFountain;
  Graphfiller filler;
  void init(const std::string& filename);

 public:
  EBPF(Results& r, FileFountain& f);
  void run() override;
  void restart();
  ~EBPF() {}
  bool hasCycle();
  bool hasUnusedInstruction();
};

#endif  // EBPF_H_
