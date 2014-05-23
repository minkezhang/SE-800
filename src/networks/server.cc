#include "../engines/cleanup/cleanup.h"
#include "netpacket.h"
#include "packetprotos.pb.h"
#include "server.h"
#include "../classes/ship.h"
#include "../classes/control.h"
#include "../classes/player.h"
#include "../classes/event.h"
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
#include <vector>
#include <mutex>

int num_clients = 0;
std::mutex num_clients_lock;

Server::Server(WorldEngine *world, CleanupEngine *cleanup) {
	this->server_socketfd = -1;
	this->world = world;
	this->cleanup = cleanup;
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
	sendto(client_socketfd, gen_packet.packet().data(), gen_packet.packet().size(), 0,
		(struct sockaddr *) &clientaddr, sizeof(clientaddr));

	// TODO -- get return codes from sendto
	return(1);
}

void *Server::accept_clients(void *args) {
	std::cout << "Ready to accept clients" << std::endl;
	int *port = (int *) args;
	std::cout << "Port number is " << *port << std::endl;
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
		std::cout << "SETSOCKOPT network error." << std::endl;
	if (::bind(this->server_socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
		std::cout << "BIND network error." << std::endl;
	if (listen(this->server_socketfd, 5) != 0)
		std::cout << "LISTEN network error." << std::endl;

	while(1) {
		// Exit the server if the last client has disconnected.
		num_clients_lock.unlock();

		*clientSocket = accept(this->server_socketfd, (struct sockaddr *) clientAddr, &sinSize);
		if (*clientSocket == -1)
			break;

		std::cout << "Found a client!" << std::endl;
		setsockopt(*clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		std::cout << "THIS IS CLIENT SOCKETFD: " << *clientSocket << std::endl;
		// DO WE HAVE TO ALLOCATE CLIENTADDR STRUCT AND CLIENTSOCKET INFO???
		this->client_fd_list.push_back(*clientSocket);
		this->client_id_to_sockaddr.insert(std::pair<int, struct sockaddr_in>(*clientSocket, *clientAddr));

		// Pass on arguments to worker thread

		// THIS NEEDS TO BE FREED LATER ON!!
		serve_client_args *args = (serve_client_args *) malloc(sizeof(serve_client_args));
		args->server_socketfd = this->server_socketfd;
		args->client_socketfd = *clientSocket;
		args->world = this->world;
		args->cleanup = this->cleanup;
		if (pthread_create(&worker_thread, NULL, serve_client, args) != 0) {
			std::cout << "Could not create a worker thread." << std::endl;
			num_clients_lock.lock();
			num_clients--;
			num_clients_lock.unlock();
			close(*clientSocket);
		}
	}
	return NULL;
}

void * Server::serve_client(void *args) {
	std::cout << "server_client spawned\n";
	// Make sure ending this thread doesn't kill the server.
	pthread_detach(pthread_self());

	num_clients_lock.lock();
	num_clients++;
	num_clients_lock.unlock();

	Server serv_utils(NULL, NULL);
	serve_client_args *sockets = (serve_client_args *) args;
	int client_socketfd = sockets->client_socketfd;
	WorldEngine *world = sockets->world;
	CleanupEngine *cleanup = sockets->cleanup;

	// Send a ship init packet to client.
	Player *p = new Player("Name", client_socketfd);
	Ship *ship = world->join(p);
	world->get_physics_engine()->get_environment()->add_projectile(ship);
	p->set_ship(ship);
	protos::RenderedObj ship_packet;
	PacketUtils::fill_obj_packet(&ship_packet, ship, ObjType::SHIP);
	NetPacket packet;
	PacketUtils::make_packet(&packet, PacketType::SHIP_INIT, (void *) ship, NULL);
	serv_utils.send_to_client(&packet, client_socketfd);

	// Receive UI updates from client.
	int bufLen = 6000;
	int nbytes;
	char inputBuf[bufLen];
	char buildBuf[bufLen];
	int buildLen = 0;
	memset(inputBuf, 0, bufLen);
	memset(buildBuf, 0, bufLen);

	int packet_size = -1;
	while ((nbytes = recv(client_socketfd, inputBuf, bufLen, 0))) {
		// Check if client has disconnected
		if (nbytes <= 0)
			break;
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
				std::string payload(buildBuf + sizeof(uint32_t) + sizeof(uint32_t), payload_size);

				if (packet_type == PacketType::CONTROL_INPUT) {
					protos::ControlInput control_input_packet;
					control_input_packet.ParseFromString(payload);
					if (control_input_packet.action() == Action::ACCEL) {
						std::cout << "Received Accel packet." << std::endl;
						ServerControl::update_physics(p->get_ship()->get_id(), Action::ACCEL, NULL, world->get_physics_engine());
					} else if (control_input_packet.action() == Action::RESET_ACCEL) {
						std::cout << "Received Reset Accel packet." << std::endl;
						ServerControl::update_physics(p->get_ship()->get_id(), Action::RESET_ACCEL, NULL, world->get_physics_engine());
					} else if (control_input_packet.action() == Action::BRAKE) {
						std::cout << "Received Brake packet." << std::endl;
						ServerControl::update_physics(p->get_ship()->get_id(), Action::BRAKE, NULL, world->get_physics_engine());
					} else if (control_input_packet.action() == Action::ROLL_TILT) {
						std::cout << "Received Roll tilt packet." << std::endl;
						float tilt = control_input_packet.tilt();
						ServerControl::update_physics(p->get_ship()->get_id(), Action::ROLL_TILT, (void *) &tilt, world->get_physics_engine());
					} else if (control_input_packet.action() == Action::PITCH_TILT) {
						std::cout << "Received Pitch tilt packet." << std::endl;
						float tilt = control_input_packet.tilt();
						ServerControl::update_physics(p->get_ship()->get_id(), Action::PITCH_TILT, (void *) &tilt, world->get_physics_engine());
					} else if (control_input_packet.action() == Action::BULLET) {
						std::cout << "Received Bullet packet." << std::endl;
					}
				} else if (packet_type == PacketType::EVENT_ACK) {
					// TODO: Handle event ack packet receipt.
				} else if (packet_type == PacketType::OBJS_AND_EVENTS_REQ) {
					NetPacket objs_and_events_packet;
					std::vector<Projectile*> objs;
					objs = world->get_physics_engine()->get_environment()->get_neighbors(p->get_ship());

					std::vector<Event *> events = cleanup->send_event_vec(client_socketfd, num_clients);
					PacketUtils::make_packet(&objs_and_events_packet, PacketType::OBJS_AND_EVENTS, (void *) &objs, (void *) &events);
					serv_utils.send_to_client(&objs_and_events_packet, client_socketfd);
				} else {
					std::cout << "Received Invalid Packet Type" << std::endl;
				}
				if (buildLen > packet_size) {
					// Case if there are more packets in net buffer.
					// Copy other packets to beginning of buffer and reset build len.
					char tempBuf[bufLen - packet_size];
					memcpy(tempBuf, buildBuf + packet_size, bufLen - packet_size);
					memcpy(buildBuf, tempBuf, bufLen - packet_size);
				}
				buildLen -= packet_size;
				packet_size = -1;
			} else {
				break;
			}
		}
	}

	num_clients_lock.lock();
	num_clients--;
	if (num_clients == 0) {
		// If no more clients connected, end game
		shutdown(sockets->server_socketfd, SHUT_RDWR);
	}
	num_clients_lock.unlock();
	pthread_exit(NULL);
	return NULL;
}

NetPacket Server::receive_from_client(int client_fd) {
	return NetPacket();
}
