// Copyright [2020]<Jonathan David Rosenblatt>
#define _POSIX_C_SOURCE 201112L

#include "common_socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int socket_init(socket_t* socket) {
  if (socket == NULL) return -1;
  socket->fd = -1;
  return 0;
}

int socket_destroy(socket_t* socket) {
  if (socket == NULL || shutdown(socket->fd, SHUT_RDWR) == -1 ||
      close(socket->fd) == -1)
    return -1;
  return 0;
}

int socket_accept(socket_t* socket, socket_t* client) {
  if (socket == NULL || client == NULL) return -1;
  char addressBuf[INET_ADDRSTRLEN];
  struct sockaddr_in address;
  socklen_t addressLength = (socklen_t)sizeof(address);

  int newSocket =
      accept(socket->fd, (struct sockaddr*)&address, &addressLength);
  inet_ntop(AF_INET, &(address.sin_addr), addressBuf, INET_ADDRSTRLEN);
  client->fd = newSocket;
  return 0;
}

/*
 * Función auxiliar que realiza el getaddrinfo(3) en función de los parámetros
 * ingresados. Devuelve una lista de posibles conexiones válidas.
 * Precondiciones: socket != NULL && port != NULL.
 * Postcondiciones: devuelve la lista de direcciones, donde el pasaje de
 * información será mediante un stream continuo de datos. Devuelve NULL en caso
 * de error, el struct addrinfo conseguido de lo contrario
 */
static struct addrinfo* get_addr_info(socket_t* socket, const char* port,
                                      const char* ip) {
  if (socket == NULL || port == NULL) return NULL;
  struct addrinfo* address_list;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));  // Inicializa en cero.
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;

  if (getaddrinfo(ip, port, &hints, &address_list) != 0) {
    fprintf(stderr, "Error, no hay conexiones disponibles.\n");
    socket_destroy(socket);
    return NULL;
  }
  return address_list;  // Es válido devolver este puntero ya que vive en el
                        // heap.
}

// CLIENT ONLY
int socket_connect(socket_t* self, const char* port, const char* ip) {
  if (self == NULL || port == NULL || ip == NULL) return -1;
  struct addrinfo* address_list;
  if ((address_list = get_addr_info(self, port, ip)) == NULL) return -1;

  for (struct addrinfo* conex = address_list; conex != NULL;
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    if (extra_fd == -1) {
      continue;
    } else if (connect(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
      close(extra_fd);
      continue;
    } else {
      self->fd = extra_fd;
      break;  // I'm in...
    }
  }
  freeaddrinfo(address_list);

  return (self->fd == -1);
}

// SERVER ONLY
int socket_bind(socket_t* self, char* port) {
  if (self == NULL || port == NULL) return -1;
  struct addrinfo* address_list;
  if ((address_list = get_addr_info(self, port, NULL)) == NULL) return -1;

  int val = 1;
  for (struct addrinfo* conex = address_list; conex != NULL;
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    setsockopt(extra_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (extra_fd == -1) {
      continue;
    } else if (bind(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
      close(extra_fd);
      continue;
    } else {
      self->fd = extra_fd;
      break;  // I'm in...
    }
  }
  freeaddrinfo(address_list);

  return (self->fd == -1);
}

// SERVER ONLY
int socket_listen(socket_t* socket, unsigned int queueSize) {
  if (socket == NULL || listen(socket->fd, queueSize) == -1) {
    socket_destroy(socket);
    return -1;
  }
  return 0;
}

int socket_send(socket_t* socket, char* msg, size_t len) {
  if (socket == NULL || msg == NULL) return -1;
  unsigned int already_sent = 0;
  unsigned int remaining = len;
  while (already_sent < len) {
    int just_sent = 0;
    if ((just_sent = send(socket->fd, &msg[already_sent], remaining,
                          MSG_NOSIGNAL)) == -1) {
      return -1;
    }
    already_sent += just_sent;
    remaining -= just_sent;
  }
  return already_sent;
}

int socket_recv(socket_t* socket, char* buf, size_t len) {
  if (socket == NULL || buf == NULL) return -1;
  unsigned int already_read = 0;
  unsigned int remaining = len;
  while (already_read < len) {
    int just_read = 0;
    if ((just_read = recv(socket->fd, &buf[already_read], remaining, 0)) == -1) {
      return -1;
    } else if (just_read == 0) {
      break;
    }
    already_read += just_read;
    remaining -= just_read;
  }
  return already_read;
}
