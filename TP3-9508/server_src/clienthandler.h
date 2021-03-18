#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_

#include <string>

#include "../common_src/socket.h"
#include "referencefountain.h"
#include "thread.h"

class Clienthandler : public Thread {
 private:
  const std::string& rootfile;
  bool isDeadB;
  Socket self;
  Referencefountain& refs;

 public:
  Clienthandler(const std::string& file, Socket s, Referencefountain& r);
  void run() override;
  bool isDead() { return isDeadB; }
};

#endif  // CLIENTHANDLER_H_
