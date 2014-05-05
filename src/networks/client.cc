#include "client.h"
#include "netpacket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <string>

#define SOCKET_ERROR -1

bool ClientNetUtils::connect_to_server(int port, string ip) {
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
  servaddr.sin_port = htons(port);

  if (connect(server_sockfd, (struct sockaddr *) &servaddr,
    sizeof(servaddr)) == SOCKET_ERROR) {
    server_sockfd = -1;
    return false;
  }
  return true;
}

bool send_to_server(NetPacket* packet) {
  return true;
}

NetPacket* receive_from_server() {
  return NULL;
}
