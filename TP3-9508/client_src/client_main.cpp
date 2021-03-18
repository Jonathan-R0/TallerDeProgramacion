#include <fstream>
#include <iostream>

#include "clientmanager.h"

#define GENERIC_ERROR "A weird error just occured in the client..."

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 0;
  }
  Clientmanager worker(argv[1], argv[2]);

  try {
    worker.start();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  return 0;
}
