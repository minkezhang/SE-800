#ifndef _CLIENTNETUTILS_H
#define _CLIENTNETUTILS_H

#include "netpacket.h"
#include "packetprotos.pb.h"

#include <netinet/in.h>
#include <string>
#include <stack>

using namespace std;

class ClientNetUtils {
	public:
		bool connect_to_server(int port, string ip);
		bool send_to_server(NetPacket *packet);
		bool receive_from_server();
		void fill_packet_queue(protos::ObjsAndEventsPacket);
		void close_connection();

	private:
		int server_sockfd;
		struct sockaddr_in servaddr;
		stack<protos::RenderedObj> obj_queue;
//		stack<Event> event_queue;
};

#endif
