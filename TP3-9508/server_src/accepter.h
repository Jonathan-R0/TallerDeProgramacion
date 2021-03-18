#ifndef ACCEPTER_H_
#define ACCEPTER_H_

#include <list>
#include <string>

#include "../common_src/socket.h"
#include "clienthandler.h"
#include "referencefountain.h"
#include "thread.h"

typedef std::list<Clienthandler*>::iterator iterator_t;

class Accepter : public Thread {
 private:
  Referencefountain references;
  std::list<Clienthandler*> clientlist;
  std::string rootfile;
  Socket server;

 public:
  void stop();
  Accepter(char* p, const std::string& r);
  ~Accepter();
  void removeDeadClients();
  void run() override;
};

#endif  // ACCEPTER_H_
