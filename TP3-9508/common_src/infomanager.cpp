#include "infomanager.h"

#include <netdb.h>

#include <cstring>
#include <iostream>
#include <string>

#include "socket.h"

#define BYTES_A_LEER 32
#define RECVERROR "Died receiving info with errno: "
#define SENDERROR "Died sending info with errno: "

void Infomanager::recvInfo(Socket& self, std::string& msg) {
  char buf[BYTES_A_LEER] = {};
  int read;
  while ((read = self.recv(sizeof(buf) - 1, buf)) != 0) {
    if (read == -1) {
      std::cerr << RECVERROR << hstrerror(errno) << std::endl;
    }
    msg += buf;
    memset(buf, 0, sizeof(buf));
  }
  self.shutdown(SHUT_RD);
}

void Infomanager::sendInfo(Socket& self, std::string& msg) {
  if (self.send(msg.length(), msg.c_str()) == -1)
    std::cerr << SENDERROR << hstrerror(errno) << std::endl;
  self.shutdown(SHUT_WR);
}

void Infomanager::sendInfoFromStdin(Socket& self) {
  std::string msg;
  std::string placeholder;
  while (std::getline(std::cin, placeholder)) msg += placeholder + "\n";
  this->sendInfo(self, msg);
}
