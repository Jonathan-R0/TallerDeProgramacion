#ifndef INFOMANAGER_H_
#define INFOMANAGER_H_

#include <string>

#include "socket.h"

class Infomanager {
 public:
  void recvInfo(Socket& self, std::string& rootfile);
  void sendInfo(Socket& self, std::string& msg);
  void sendInfoFromStdin(Socket& self);
};

#endif  // INFOMANAGER_H_
