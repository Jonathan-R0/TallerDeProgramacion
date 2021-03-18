#include "executer.h"

#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "eBPF.h"
#include "fileFountain.h"
#include "results.h"
#include "thread.h"

void Executer::run(int argc, char* argv[]) {
  FileFountain files(argc, argv);
  Results results;
  holders.reserve(numberOfThreads);

  for (int i = 0; i < numberOfThreads; i++) {
    holders.push_back(new EBPF(results, files));
  }

  for (auto& it : holders) it->start();
  for (auto& it : holders) {
    it->join();
    delete it;
  }
  results.printResults();
}
