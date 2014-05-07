#include "netpacket.h"
#include "server.h"

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

Server::Server(int port) {
  this->accept_clients((void *)&port);
}

Server::~Server() {
  close(this->server_socketfd);
}

int Server::get_client_fd(int id) {
}

bool Server::send_to_client(NetPacket *packet, int client_id) {
}

void *Server::accept_clients(void *args) {
  std::cout << "ABOUT TO LISTEN FOR CLIENTS" << std::endl;
  int *port = (int *) args;
  std::cout << "port number is " << *port << std::endl;
  int num_clients = 0;
  int clientSocket;
  pthread_t worker_thread;
  struct sockaddr_in serverAddr;
  struct sockaddr_in clientAddr;
  int yes = 1;
  socklen_t sinSize = sizeof(struct sockaddr_in);

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(*port);
  serverAddr.sin_addr.s_addr = INADDR_ANY;

  this->server_socketfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (setsockopt(this->server_socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) != 0)
    std::cout << "ERROR WITH SETSOCKOPT" << std::endl;
  if (::bind(this->server_socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
    std::cout << "ERROR WITH BIND" << std::endl;
  if (listen(this->server_socketfd, 5) != 0)
    std::cout << "ERROR WITH LISTEN " << std::endl;

  while(1) {
    clientSocket = accept(this->server_socketfd, (struct sockaddr *) &clientAddr, &sinSize);
    std::cout << "Found a client!" << std::endl;
    num_clients++;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    // Retrieve client hostname
    struct hostent *he;
    struct in_addr ipv4addr;
    char *IP = inet_ntoa(clientAddr.sin_addr);
    inet_pton(AF_INET, IP, &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof(ipv4addr), AF_INET);
    // Pass on arguments to worker thread

    if (pthread_create(&worker_thread, NULL, serve_client, &this->server_socketfd) != 0) {
      std::cout << "Could not create a worker thread." << std::endl;
      num_clients--;
      close(clientSocket);
      pthread_exit(NULL);
    }

    if (num_clients == 1) {
      std::cout << "ONE PLAYER CONNECTED!" << std::endl;
    }
  }

}

void * Server::serve_client(void *args) {
}

NetPacket Server::receive_from_client(int client_fd) {
}
