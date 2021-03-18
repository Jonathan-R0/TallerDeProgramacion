#include "results.h"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define CORRECT " GOOD\n"
#define FAILHASCYCLES " FAIL: cycle detected\n"
#define FAILHASUNUSED " FAIL: unused instructions detected\n"

static int cmp(const std::string& a, const std::string& b) { return a < b; }

static void sort(std::vector<std::string>& v) {
  std::sort(v.begin(), v.end(), cmp);
}

void Results::addResult(std::string file, bool hasCycleB, bool hasUnusedOpB) {
  std::unique_lock<std::mutex> lock(m);
  allops.push_back(file);
  if (hasCycleB) {
    hasCycle.push_back(std::move(file));
  } else if (hasUnusedOpB) {
    hasUnusedInstructions.push_back(std::move(file));
  } else {
    good.push_back(std::move(file));
  }
}

void Results::printResults() {
  sort(allops);
  for (std::string& s : allops) {
    if (find(good.begin(), good.end(), s) != good.end())
      std::cout << s << CORRECT;
    else if (find(hasCycle.begin(), hasCycle.end(), s) != hasCycle.end())
      std::cout << s << FAILHASCYCLES;
    else
      std::cout << s << FAILHASUNUSED;
  }
}
