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

std::queue<protos::RenderedObj *> *ship_que;
std::queue<protos::ObjsAndEventsPacket *> *objs_que;
std::mutex *q_lock;
protos::RenderedObj *init_ship;

ClientNetUtils::ClientNetUtils (std::queue<protos::ObjsAndEventsPacket *> *objs_queue, std::queue<protos::RenderedObj *> *s_queue, std::mutex *que_lock) {
	objs_que = objs_queue;
	ship_que = s_queue;
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
		cout << "Connection failed with errorno " << errno << endl;
		this->server_sockfd = -1;
		return false;
	}
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
	sendto(this->server_sockfd, gen_packet.packet().data(), gen_packet.packet().size(), 0,
		(struct sockaddr *) &this->servaddr, sizeof(this->servaddr));
	return true;
}

void * ClientNetUtils::receive_from_server() {
	if (this->server_sockfd == -1)
		return NULL;

	int bufLen = 30000;
	int nbytes;
	char inputBuf[bufLen];
	char buildBuf[bufLen];
	int buildLen = 0;
	memset(inputBuf, 0, bufLen);
	memset(buildBuf, 0, bufLen);

	int packet_size = -1;
	while ((nbytes = recv(server_sockfd, inputBuf, bufLen, 0)) && (nbytes > 0)) {

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
				std::string payload(buildBuf + sizeof(uint32_t) + sizeof(uint32_t), payload_size);

				// Push packet onto corresponding queue.
				if (packet_type == PacketType::SHIP_INIT) {
					// cout << "Received ship init packet." << endl;
					protos::ShipInitPacket *ship_init_packet = new protos::ShipInitPacket;
					ship_init_packet->ParseFromString(payload);
					protos::RenderedObj *ship = new protos::RenderedObj(ship_init_packet->ship());
					//TODO: Use smart pointers for RenderedObj creation.
					q_lock->lock();
					ship_que->push(ship);
					q_lock->unlock();
				} else if (packet_type == PacketType::OBJS_AND_EVENTS) {
					// cout << "Received objs and events packet." << std::endl;
					protos::ObjsAndEventsPacket *objs_and_events_packet = new protos::ObjsAndEventsPacket;
					objs_and_events_packet->ParseFromString(payload);
					q_lock->lock();
					objs_que->push(objs_and_events_packet);
					q_lock->unlock();
				} else {
					cout << "Received Invalid Packet Type" << endl;
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
	return NULL;
}

void ClientNetUtils::close_connection() {
	close(this->server_sockfd);
}
