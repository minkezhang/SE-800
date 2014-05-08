#include "client.h"
#include "netpacket.h"
#include "packetprotos.pb.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <errno.h>

#define SOCKET_ERROR -1

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

bool ClientNetUtils::receive_from_server() {
  cout << "ENTERING RECEIVE FROM SERVER" << endl;
	if (this->server_sockfd == -1)
		return false;

	int bufLen = 6000;
	int nbytes;
	char inputBuf[bufLen];
	char buildBuf[bufLen];
	int buildLen = 0;
	memset(inputBuf, 0, bufLen);
	memset(buildBuf, 0, bufLen);

	int packet_size = -1;
	while (nbytes = recv(this->server_sockfd, inputBuf, bufLen, 0) > 0) {

    cout << "NBYTES IS " << nbytes << endl;
		if (nbytes + buildLen > buildLen)
			nbytes = bufLen - buildLen;
		// Move all received bytes over to build buf
		memcpy(buildBuf + buildLen, inputBuf, nbytes);
		buildLen += nbytes;

    cout << "CHECKPOINT ONE" << endl;
		// Clear input buf
		memset(inputBuf, 0, bufLen);

		// Parse build buf for all received protos.
		if (packet_size == -1) {
			// Assume this is the beginning of a new packet. Try to set pack size.
			if (buildLen >= 4) {
				memcpy(&packet_size, buildBuf, sizeof(uint32_t));
				packet_size = ntohl(packet_size);
				
				// One complete packet is in the buffer.
				if (buildLen >= packet_size) {
					int packet_type;
          cout << "CHECKPOINT ONE.FIVE" << endl;
					memcpy(&packet_type, buildBuf + sizeof(uint32_t), sizeof(uint32_t));
					packet_type = ntohl(packet_type);

          cout << "CHECKPOINT TWO" << endl;
					int payload_size = packet_size - sizeof(uint32_t) - sizeof(uint32_t);
					char payload[payload_size];
					memcpy(payload, buildBuf + sizeof(uint32_t) + sizeof(uint32_t), payload_size);

					if (packet_type == PacketType::SHIP_INIT) {
						protos::ShipInitPacket ship_init_packet;
						ship_init_packet.ParseFromString(payload);
						protos::RenderedObj ship = ship_init_packet.ship();
						cout << "THIS IS SHIP ID AND MASS: " << ship.id() << " " << ship.mass() << endl;
					} else if (packet_type == PacketType::OBJS_AND_EVENTS) {
						protos::ObjsAndEventsPacket objs_and_events_packet;
						objs_and_events_packet.ParseFromString(payload);
						fill_packet_queue(objs_and_events_packet);
					} else {
						cout << "Received Invalid Packet Type" << endl;
					}
          cout << "CHECKPOINT THREE" << endl;
					packet_size = -1;
					// There are more packets in net buffer.
					if (buildLen > packet_size) {
						// Copy other packets to beginning of buffer and reset build len.
            cout << "CHECKPOINT FOUR" << endl;
						memcpy(buildBuf, buildBuf + packet_size, bufLen - packet_size);
						buildLen =- packet_size;
            cout << "CHECKPOINT FIVE" << endl;
						// TODO: CALL RECURSIVE FUNCTION TO PARSE REMAINING BUILDBUF CONTENTS.
					}
				}
			}
		}
	}

	return true;
}

void ClientNetUtils::fill_packet_queue(protos::ObjsAndEventsPacket) {
}

void ClientNetUtils::close_connection() {
	close(this->server_sockfd);
}
