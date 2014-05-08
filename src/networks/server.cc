#include "netpacket.h"
#include "packetprotos.pb.h"
#include "server.h"
#include "../classes/ship.h"

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <map>


void build_ship(Ship *ship) {
	vector<float> pos { 1,2,3 };
	ship->set_d(pos);
	vector<float> vel { 4,5,6 };
	ship->set_v(vel);
	ship->set_a(7.0);
		 
	vector<float> pitch { 10,11,12 };
	ship->set_p(pitch);
	vector<float> yaw { 13,14,15 };
	ship->set_y(yaw);
	vector<float> roll { 16,17,18 };
	ship->set_r(roll);
		 
	ship->set_p_dot(6.6);
	ship->set_r_dot(7.7);
}

Server::Server() {
}

Server::~Server() {
  close(this->server_socketfd);
}

void Server::start_server(int port) {
  this->accept_clients((void *)&port);
}

int Server::get_client_fd(int id) {
}

bool Server::send_to_client(NetPacket *packet, int client_id) {
  int client_socketfd = client_id;
  struct sockaddr_in clientaddr = client_id_to_sockaddr[client_id];

  protos::GeneralPacket gen_packet;
  gen_packet.ParseFromString(packet->serialized_packet);

  uint32_t network_byte_len = htonl(packet->packet_len);
  uint32_t network_byte_type = htonl(gen_packet.packettype());


  std::cout << "PACKET SIZE SHOULD BE : " << sizeof(gen_packet.packet()) + 4 + 4 << " ACTUAL SIZE IS " << packet->packet_len << std::endl;

  // Send packet length
  sendto(client_socketfd, &network_byte_len, sizeof(uint32_t), 0,
    (struct sockaddr *) &clientaddr, sizeof(clientaddr));
  // Send packet type
  sendto(client_socketfd, &network_byte_type, sizeof(uint32_t), 0,
    (struct sockaddr *) &clientaddr, sizeof(clientaddr));
  // Send packet payload
  sendto(client_socketfd, gen_packet.packet().c_str(), sizeof(gen_packet.packet()), 0,
    (struct sockaddr *) &clientaddr, sizeof(clientaddr));

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

    // DO WE HAVE TO ALLOCATE CLIENTADDR STRUCT AND CLIENTSOCKET INFO???
    this->client_fd_list.push_back(clientSocket);
    this->client_id_to_sockaddr.insert(std::pair<int, struct sockaddr_in>(clientSocket, clientAddr));

    
    // Pass on arguments to worker thread

    // THIS NEEDS TO BE FREED LATER ON!!
    serve_client_args *args = (serve_client_args *) malloc(sizeof(serve_client_args));
    args->server_socketfd = this->server_socketfd;
    args->client_socketfd = clientSocket;
    if (pthread_create(&worker_thread, NULL, serve_client, args) != 0) {
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
  // Make sure ending this thread doesn't kill the server.
  pthread_detach(pthread_self());

  Server serv_utils;
  serve_client_args *sockets = (serve_client_args *) args;
  int client_socketfd = sockets->client_socketfd;
  int server_socketfd = sockets->server_socketfd;

  // SEND A TEST SHIP INIT PACKET TO CLIENT
  Ship ship(1, 1, 2.0, 2.0);
  build_ship(&ship);
  protos::RenderedObj ship_packet;
  PacketUtils::fill_obj_packet(&ship_packet, &ship);
  NetPacket packet;

  PacketUtils::make_packet(&packet, PacketType::SHIP_INIT, (void *) &ship, NULL);
 
  serv_utils.send_to_client(&packet, client_socketfd);

  pthread_exit(NULL);
}

NetPacket Server::receive_from_client(int client_fd) {
}
