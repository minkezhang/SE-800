#include "client.h"
#include "netpacket.h"
#include "packetprotos.pb.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <queue>
#include <unistd.h>
#include <mutex>

#define SOCKET_ERROR -1

queue<protos::RenderedObj> *que;
std::mutex *q_lock;

ClientNetUtils::ClientNetUtils (queue<protos::RenderedObj> *queue, std::mutex *que_lock) {
	que = queue;
  q_lock = que_lock;
}

bool ClientNetUtils::connect_to_server(int port, string ip) {
	this->server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&this->servaddr, 0, sizeof(this->servaddr));
	this->servaddr.sin_family = AF_INET;
	this->servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
	this->servaddr.sin_port = htons(port);

	if (connect(this->server_sockfd, (struct sockaddr *) &this->servaddr,
		sizeof(this->servaddr)) == SOCKET_ERROR) {
		cout << "CONNECT FAILED" << errno << endl;
		this->server_sockfd = -1;
		return false;
	}
	cout << "SERVER SOCKFD IS " << this->server_sockfd << endl;
	return true;
}

bool ClientNetUtils::send_to_server(NetPacket* packet) {
	if (this->server_sockfd == -1)
		return false;

	protos::GeneralPacket gen_packet;
	gen_packet.ParseFromString(packet->serialized_packet);

	uint32_t network_byte_len = htonl(packet->packet_len);
	uint32_t network_byte_type = htonl(gen_packet.packettype());

	// Send packet length	
	sendto(this->server_sockfd, &network_byte_len, sizeof(uint32_t), 0,
		(struct sockaddr *) &this->servaddr, sizeof(this->servaddr));
	// Send packet type
	sendto(this->server_sockfd, &network_byte_type, sizeof(uint32_t), 0,
		(struct sockaddr *) &this->servaddr, sizeof(this->servaddr));
	// Send packet payload
	sendto(this->server_sockfd, gen_packet.packet().c_str(), sizeof(gen_packet.packet()), 0,
		(struct sockaddr *) &this->servaddr, sizeof(this->servaddr));
	return true;
}

void * ClientNetUtils::receive_from_server(void *args) {
	// Make sure ending this thread doesn't kill the client.
	pthread_detach(pthread_self());

	int *server_sockfd = (int *) args;
	cout << "ENTERING RECEIVE FROM SERVER" << endl;
	if (*server_sockfd == -1)
		return NULL;

	int bufLen = 6000;
	int nbytes;
	char inputBuf[bufLen];
	char buildBuf[bufLen];
	int buildLen = 0;
	memset(inputBuf, 0, bufLen);
	memset(buildBuf, 0, bufLen);

	int packet_size = -1;
	while ((nbytes = recv(*server_sockfd, inputBuf, bufLen, 0)) && (nbytes > 0)) {

		cout << "NBYTES RECEIVED IS " << nbytes << endl;
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
				// Assume this is the beginning of a new packet. Try to set pack size.
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

				if (packet_type == PacketType::SHIP_INIT) {
					cout << "RECEIVED SHIP PACKET!" << endl;
					protos::ShipInitPacket *ship_init_packet = new protos::ShipInitPacket;
					ship_init_packet->ParseFromString(payload);
					protos::RenderedObj *ship = new protos::RenderedObj(ship_init_packet->ship());
					//TODO: REMEMBER TO FREE THESE OBJECTS LATER!
			//						protos::RenderedObj ship = ship_init_packet->ship();
					cout << "THIS IS SHIP ID AND MASS: " << ship->id() << " " << ship->mass() << endl;
					q_lock->lock();
					fill_packet_queue(que, ship);
					q_lock->unlock();
					std::cout << "DONE FILLING QUEUE" << std::endl;
				} else if (packet_type == PacketType::OBJS_AND_EVENTS) {
					protos::ObjsAndEventsPacket objs_and_events_packet;
					objs_and_events_packet.ParseFromString(payload);
					//fill_packet_queue(*que, objs_and_events_packet);
					packet_size = -1;
				} else {
					cout << "Received Invalid Packet Type" << endl;
				}
				// There are more packets in net buffer.
				if (buildLen > packet_size) {
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
	return NULL;
}

void ClientNetUtils::fill_packet_queue(queue<protos::RenderedObj> *obj_queue, protos::RenderedObj *packet) {
	obj_queue->push(*packet);
}

void ClientNetUtils::close_connection() {
	close(this->server_sockfd);
}
