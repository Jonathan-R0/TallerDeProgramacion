#include "socket.h"

#include <netdb.h>
#include <unistd.h>

#include <cstring>
#include <exception>
#include <iostream>
#include <string>

#include "socketclosedexception.h"

#define ACCEPT_ERROR "Error on server's accept, the socket was not open."
#define GET_ADDR_INFO_ERROR "Error on client's getaddrinfo."

Socket::~Socket() {
  if (fd != -1) {
    ::shutdown(fd, SHUT_RDWR);
    close(fd);
  }
}

Socket& Socket::operator=(Socket&& other) {
  if (this != &other && this->fd == -1) {
    this->fd = other.fd;
    other.fd = -1;
  }
  return *this;
}

Socket::Socket(Socket&& other) {
  this->fd = other.fd;
  other.fd = -1;
}

void Socket::shutdown(int channel) {
  if (fd != -1) ::shutdown(fd, channel);
}

struct addrinfo* Socket::get_addr_info(const char* port, const char* ip) {
  struct addrinfo* address_list;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = (ip == nullptr) ? AI_PASSIVE : 0;

  if (getaddrinfo(ip, port, &hints, &address_list) != 0) return nullptr;
  return address_list;
}

void Socket::connect(const char* port, const char* ip) {
  struct addrinfo* address_list = nullptr;
  if ((address_list = this->get_addr_info(port, ip)) == nullptr)
    throw std::invalid_argument(GET_ADDR_INFO_ERROR);

  for (struct addrinfo* conex = address_list; conex != nullptr;
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    if (extra_fd == -1) {
      continue;
    } else if (::connect(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
      close(extra_fd);
      continue;
    } else {
      fd = extra_fd;
      break;
    }
  }
  freeaddrinfo(address_list);
}

Socket Socket::accept() {
  int extra_fd = ::accept(fd, nullptr, nullptr);
  if (extra_fd == -1) throw SocketClosedException(ACCEPT_ERROR);
  return (Socket(extra_fd));
}

int Socket::bind(const char* port) {
  struct addrinfo* address_list;

  if ((address_list = this->get_addr_info(port, nullptr)) == nullptr) return -1;

  int val = 1;
  for (struct addrinfo* conex = address_list; conex != nullptr;
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    setsockopt(extra_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (extra_fd == -1) {
      continue;
    } else if (::bind(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
      close(extra_fd);
      continue;
    } else {
      fd = extra_fd;
      break;
    }
  }
  freeaddrinfo(address_list);
  return (fd == -1);
}

int Socket::listen(unsigned int queueSize) {
  return (::listen(fd, queueSize) == -1);
}

int Socket::send(unsigned int len, const char* msg) {
  unsigned int already_sent = 0;
  unsigned int remaining = len;
  while (already_sent < len) {
    int just_sent = 0;
    if ((just_sent = ::send(fd, &msg[already_sent], remaining, MSG_NOSIGNAL)) ==
        -1) {
      return -1;
    }
    already_sent += just_sent;
    remaining -= just_sent;
  }
  return already_sent;
}

int Socket::recv(unsigned int len, char* buf) {
  unsigned int already_read = 0;
  unsigned int remaining = len;
  while (already_read < len) {
    int just_read = 0;
    if ((just_read = ::recv(fd, &buf[already_read], remaining, 0)) == -1) {
      return -1;
    } else if (just_read == 0) {
      break;
    }
    already_read += just_read;
    remaining -= just_read;
  }
  return already_read;
}
