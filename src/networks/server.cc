#include "netpacket.h"
#include "packetprotos.pb.h"
#include "server.h"
#include "../classes/ship.h"
#include "../classes/control.h"
#include "../classes/pilot.h"
#include "../engines/world/world.h"

#include <iostream>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <map>

Server::Server(WorldEngine *world) {
	this->server_socketfd = -1;
	this->world = world;
}

Server::~Server() {
	if (this->server_socketfd != -1)
		close(this->server_socketfd);
}

void Server::start_server(int port) {
	this->accept_clients((void *)&port);
}

int Server::get_client_fd(int id) {
	return(0);
}

bool Server::send_to_client(NetPacket *packet, int client_id) {
	int client_socketfd = client_id;
	//std::cout << "CLIENT ID IS " << client_id << std::endl;
	struct sockaddr_in clientaddr = this->client_id_to_sockaddr[client_id];

	protos::GeneralPacket gen_packet;
	gen_packet.ParseFromString(packet->serialized_packet);

	uint32_t network_byte_len = htonl(packet->packet_len);
	uint32_t network_byte_type = htonl(gen_packet.packettype());

	// Send packet length
	sendto(client_socketfd, &network_byte_len, sizeof(uint32_t), 0,
		(struct sockaddr *) &clientaddr, sizeof(clientaddr));
	// Send packet type
	sendto(client_socketfd, &network_byte_type, sizeof(uint32_t), 0,
		(struct sockaddr *) &clientaddr, sizeof(clientaddr));
	// Send packet payload
	sendto(client_socketfd, gen_packet.packet().c_str(), sizeof(gen_packet.packet()), 0,
		(struct sockaddr *) &clientaddr, sizeof(clientaddr));

	// TODO -- get return codes from sendto
	return(1);
}

void *Server::accept_clients(void *args) {
	std::cout << "ABOUT TO LISTEN FOR CLIENTS" << std::endl;
	int *port = (int *) args;
	std::cout << "port number is " << *port << std::endl;
	int num_clients = 0;
	int *clientSocket = (int *) malloc(sizeof(int));
	pthread_t worker_thread;
	struct sockaddr_in serverAddr;
	struct sockaddr_in *clientAddr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));;
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
		*clientSocket = accept(this->server_socketfd, (struct sockaddr *) clientAddr, &sinSize);
		std::cout << "Found a client!" << std::endl;
		num_clients++;
		setsockopt(*clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		std::cout << "THIS IS CLIENT SOCKETS " << *clientSocket << std::endl;
		// DO WE HAVE TO ALLOCATE CLIENTADDR STRUCT AND CLIENTSOCKET INFO???
		this->client_fd_list.push_back(1);
		std::cout << "PUSHED ONE BACK" << std::endl;
		this->client_fd_list.push_back(*clientSocket);
		this->client_id_to_sockaddr.insert(std::pair<int, struct sockaddr_in>(*clientSocket, *clientAddr));
		std::cout << "INSERTING CLIENT ID " << *clientSocket << std::endl;

		// Pass on arguments to worker thread

		// THIS NEEDS TO BE FREED LATER ON!!
		serve_client_args *args = (serve_client_args *) malloc(sizeof(serve_client_args));
		args->server_socketfd = this->server_socketfd;
		args->client_socketfd = *clientSocket;
		args->world = this->world;
		if (pthread_create(&worker_thread, NULL, serve_client, args) != 0) {
			std::cout << "Could not create a worker thread." << std::endl;
			num_clients--;
			close(*clientSocket);
			pthread_exit(NULL);
		}

		if (num_clients == 1) {
			std::cout << "ONE PLAYER CONNECTED!" << std::endl;
		}
	}
}

void * Server::serve_client(void *args) {
	std::cout << "server_client spawned\n";
	// Make sure ending this thread doesn't kill the server.
	pthread_detach(pthread_self());

	Server serv_utils(NULL);
	serve_client_args *sockets = (serve_client_args *) args;
	int client_socketfd = sockets->client_socketfd;
	WorldEngine *world = sockets->world;
	//int server_socketfd = sockets->server_socketfd;

	// SEND A TEST SHIP INIT PACKET TO CLIENT
	Pilot *p = new Pilot("Name");
	Ship *ship = world->join(p);
	//Ship ship(1, 1, 2.0, 2.0);
	//build_ship(&ship);
	protos::RenderedObj ship_packet;
	PacketUtils::fill_obj_packet(&ship_packet, ship, ObjType::SHIP);
	NetPacket packet;

	NetPacket test_objs_and_events_packet;
	std::list<Projectile *> test_objs;
	test_objs.push_back(ship);
	PacketUtils::make_packet(&test_objs_and_events_packet, PacketType::OBJS_AND_EVENTS, (void *) &test_objs, NULL);

	PacketUtils::make_packet(&packet, PacketType::SHIP_INIT, (void *) ship, NULL);
	serv_utils.send_to_client(&packet, client_socketfd);

	// RECEIVE UI UPDATES FROM CLIENT
	int bufLen = 6000;
	int nbytes;
	char inputBuf[bufLen];
	char buildBuf[bufLen];
	int buildLen = 0;
	memset(inputBuf, 0, bufLen);
	memset(buildBuf, 0, bufLen);

	int packet_size = -1;
	while ((nbytes = recv(client_socketfd, inputBuf, bufLen, 0)) && (nbytes > 0)) {
		if (nbytes + buildLen > bufLen)
			nbytes = bufLen - buildLen;
		// Move all received bytes over to build buf
		memcpy(buildBuf + buildLen, inputBuf, nbytes);
		buildLen += nbytes;

		// Clear input buf
		memset(inputBuf, 0, bufLen);

		while ((uint32_t) buildLen >= sizeof(uint32_t)) {
			// Parse build buf for all received protos.
			if (packet_size == -1) {
				// Assume this is the beginning of a packet. Try to set pack size.
				memcpy(&packet_size, buildBuf, sizeof(uint32_t));
				packet_size = ntohl(packet_size);
			}

			// One complete packet is in the buffer.
			if (buildLen >= packet_size) {
				int packet_type;
				memcpy(&packet_type, buildBuf + sizeof(uint32_t), sizeof(uint32_t));
				packet_type = ntohl(packet_type);

				int payload_size = packet_size - sizeof(uint32_t) - sizeof(uint32_t);
				char payload[payload_size];
				memcpy(payload, buildBuf + sizeof(uint32_t) + sizeof(uint32_t), payload_size);

				if (packet_type == PacketType::CONTROL_INPUT) {
					protos::ControlInput control_input_packet;
					control_input_packet.ParseFromString(payload);
					if (control_input_packet.action() == Action::ACCEL) {
						std::cout << "Received Accel packet." << std::endl;
						//serv_utils.send_to_client(&packet, client_socketfd);
						serv_utils.send_to_client(&test_objs_and_events_packet, client_socketfd);
					} else if (control_input_packet.action() == Action::BRAKE) {
						std::cout << "Received Brake packet." << std::endl;
					} else if (control_input_packet.action() == Action::BULLET) {
						std::cout << "Received Bullet packet." << std::endl;
					}
				} else if (packet_type == PacketType::EVENT_ACK) {
					// TODO: Handle event ack packet receipt.
				} else {
					std::cout << "Received Invalid Packet Type" << std::endl;
				}
				// There are more packets in net buffer.
				if (buildLen > packet_size) {
					// std::cout << "OPTIONAL CHECKPOINT" << std::endl;
					// std::cout << "BUILDLEN IS " << buildLen << " AND PACKET SIZE IS " << packet_size << std::endl;
					// Copy other packets to beginning of buffer and reset build len.
					char tempBuf[bufLen - packet_size];
					memcpy(tempBuf, buildBuf + packet_size, bufLen - packet_size);
					memcpy(buildBuf, tempBuf, bufLen - packet_size);
					// TODO: CALL RECURSIVE FUNCTION TO PARSE REMAINING BUILDBUF CONTENTS.
				}
				buildLen -= packet_size;
				packet_size = -1;
			} else {
				break;
			}
		}
	}
	pthread_exit(NULL);
	return(NULL);
}

NetPacket Server::receive_from_client(int client_fd) {
	return NetPacket();
}
