#include <iostream>

#include "executer.h"

#define ERR_INSF_ARG "Error, argument not long enough.\n"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << ERR_INSF_ARG;
    return -1;
  }
  Executer exec(argv);
  exec.run(argc, argv);
  return 0;
}
