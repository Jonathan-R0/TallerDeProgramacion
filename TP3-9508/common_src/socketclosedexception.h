#ifndef SOCKETCLOSEDEXCEPTION_H_
#define SOCKETCLOSEDEXCETPION_H_

#include <exception>
#include <string>

class SocketClosedException : public std::exception {
 private:
  std::string errormsg;

 public:
  explicit SocketClosedException(const std::string& e) : errormsg(e) {}
  virtual const char* what() const throw();
};

#endif  // SOCKETCLOSEDEXCEPTION_H_
