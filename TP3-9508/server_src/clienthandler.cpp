#include "clienthandler.h"

#include <string>
#include <utility>

#include "../common_src/infomanager.h"
#include "parser.h"
#include "response.h"

#define GENERIC_CLIENTHANDLER_ERROR "Error desconocido ocurrió en el aceptador de clientes."

Clienthandler::Clienthandler(const std::string& file, Socket s,
                             Referencefountain& r)
    : rootfile(file), isDeadB(false), self(std::move(s)), refs(r) {}

void Clienthandler::run() {
  Infomanager infomanager;
  std::string msg;
  try {
    infomanager.recvInfo(self, msg);
    Parser parse(rootfile);
    parse(msg);
    Response* responsegenerator = Response::create(parse);
    std::string answer =
        responsegenerator->generate(parse, refs);  // POLYMORPHISM!
    infomanager.sendInfo(self, answer);
    delete responsegenerator;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_CLIENTHANDLER_ERROR << std::endl;
  }
  isDeadB = true;
}
