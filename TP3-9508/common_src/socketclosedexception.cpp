#include "socketclosedexception.h"

const char* SocketClosedException::what() const throw() {
  return errormsg.c_str();
}

