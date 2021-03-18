#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/socket.h"
#include "accepter.h"
#include "parser.h"

#define GENERIC_ERROR "A weird error just occured in the server..."

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Error de argumento." << std::endl;
      return 1;
    }
    Accepter worker(argv[1], argv[2]);
    worker.start();
    std::string quit;
    while (quit != "q") {
      std::getline(std::cin, quit);
    }
    worker.stop();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
    return 1;
  }
  return 0;
}
