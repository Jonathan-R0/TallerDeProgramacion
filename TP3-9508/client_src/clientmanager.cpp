#include "clientmanager.h"

#include <iostream>
#include <string>
#include <utility>

#include "../common_src/infomanager.h"
#include "../common_src/socket.h"

Clientmanager::Clientmanager(char* ip, char* port) { self.connect(port, ip); }

void Clientmanager::start() {
  Infomanager infomanager;
  infomanager.sendInfoFromStdin(self);
  std::string msg;
  infomanager.recvInfo(self, msg);
  std::cout << msg << std::endl;
}
