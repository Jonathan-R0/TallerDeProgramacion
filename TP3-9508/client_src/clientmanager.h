#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include "../common_src/socket.h"

class Clientmanager {
 private:
  Socket self;

 public:
  Clientmanager(char* ip, char* port);
  void start();
};

#endif  // CLIENTMANAGER_H_
