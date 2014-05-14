#ifndef _CLIENTNETUTILS_H
#define _CLIENTNETUTILS_H

#include "netpacket.h"
#include "packetprotos.pb.h"

#include <netinet/in.h>
#include <string>
#include <queue>
#include <mutex>

class ClientNetUtils {
	public:
		int server_sockfd;
		ClientNetUtils(queue<protos::ObjsAndEventsPacket *> *objs_que, queue<protos::RenderedObj *> *s_que, std::mutex *que_lock);
		bool connect_to_server(int port, string ip);
		bool send_to_server(NetPacket *packet);
		void * receive_from_server();
		void close_connection();

	private:
		struct sockaddr_in servaddr;
//		stack<Event> event_queue;
};

#endif
