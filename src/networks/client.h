#ifndef _CLIENTNETUTILS_H
#define _CLIENTNETUTILS_H

#include "netpacket.h"

class ClientNetUtils {
	public:
		static bool connect(int port);
		static bool send_to_server(NetPacket packet);
		static NetPacket receive_from_server();

	private:
		int server_sockfd;
};

#endif