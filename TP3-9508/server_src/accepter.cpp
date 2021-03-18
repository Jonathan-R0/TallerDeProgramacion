#include "accepter.h"

#include <netdb.h>

#include <fstream>
#include <iostream>
#include <utility>

#include "../common_src/socketclosedexception.h"
#include "clienthandler.h"

#define QUEUESIZE 20
#define GENERIC_ACCEPTER_ERROR "Error desconocido en el hilo aceptador."

void Accepter::stop() { server.shutdown(SHUT_RDWR); }

Accepter::Accepter(char* port, const std::string& r) : rootfile(r) {
  server.bind(port);
  server.listen(QUEUESIZE);
}

Accepter::~Accepter() {
  for (Clienthandler* hilocliente : clientlist) {
    hilocliente->join();
    delete hilocliente;
  }
  this->join();
}

void Accepter::run() {
  try {
    while (true) {
      Socket newsocket = server.accept();
      Clienthandler* handler =
          new Clienthandler(rootfile, std::move(newsocket), references);
      clientlist.push_back(handler);
      handler->start();
      this->removeDeadClients();
    }
  } catch (SocketClosedException& e) {
    return;
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ACCEPTER_ERROR << std::endl;
  }
}

void Accepter::removeDeadClients() {
  for (iterator_t i = clientlist.begin(); i != clientlist.end();) {
    if ((*i)->isDead()) {
      (*i)->join();
      delete (*i);
      i = clientlist.erase(i);
    } else {
      ++i;
    }
  }
}
