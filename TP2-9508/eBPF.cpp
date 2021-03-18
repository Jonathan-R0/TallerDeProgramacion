#include "eBPF.h"

#include <bits/stdc++.h>

#include <fstream>
#include <iostream>
#include <utility>

#include "fileFountain.h"
#include "graph.h"
#include "graphFiller.h"
#include "results.h"

void EBPF::init(const std::string& filename) {
  int i = 1;
  std::ifstream reader;
  reader.open(filename, std::ifstream::in);
  while (reader.good()) {
    std::string myText;
    std::getline(reader, myText, '\n');
    if (myText.size() == 0) continue;
    filler.addInstructionToGraph(std::move(myText), i);
    i++;
  }
  reader.close();
  filler.connectLostTags();
}

EBPF::EBPF(Results& r, FileFountain& f) : results(r), fileFountain(f) {}

void EBPF::run() {
  std::string filename;
  while (!(filename = fileFountain.getNext()).empty()) {
    this->init(filename);
    results.addResult(std::move(filename), filler.hasCycle(),
                      filler.hasUnusedInstruction());
    this->restart();
  }
}

void EBPF::restart() { filler.restart(); }

bool EBPF::hasCycle() { return filler.hasCycle(); }

bool EBPF::hasUnusedInstruction() { return filler.hasUnusedInstruction(); }
