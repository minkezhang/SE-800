#ifndef _CLIENTNETUTILS_H
#define _CLIENTNETUTILS_H

#include "netpacket.h"

#include <netinet/in.h>
#include <string>

class ClientNetUtils {
	public:
		bool connect_to_server(int port, string ip);
		bool send_to_server(NetPacket *packet);
		NetPacket* receive_from_server();

  private:
		int server_sockfd;
    struct sockaddr_in servaddr;
};

#endif
