#ifndef _SERVER_H
#define _SERVER_H

#include <map>
#include <list>
#include <netinet/in.h>

#include "netpacket.h"


using namespace std;


struct serve_client_args {
	int server_socketfd;
	int client_socketfd;
};

class Server {
	public:
		// Let's say client fd = client main ship id.
		list<int> client_fd_list;

		/* server constructor actions: 
		-initialize Physics Engine object
		-spawn worker thread to accept clients
		-wait until at least one client has connected
		-start world engine & scheduler
		*/

		Server();
		~Server();
		
		void start_server(int port);
		int get_client_fd(int id);
		bool send_to_client(NetPacket *packet, int client_id);
		static void *serve_client(void *args);

		/* accept_clients actions:
		-client connections, spawning a thread for each connection */
		void *accept_clients(void *args);
	private:
		map<int, struct sockaddr_in> client_id_to_sockaddr; 
		//PhysicsEngine *physics_engine;
		int server_socketfd;
	



		/* serve_client arguments:
		-client socketfd
			 serve_client actions:
		-call physics engine function to initialize client ship 
			 (Ship :join(PILOT??))and send ship
		-send packet to client with ship object, so client can identify itself
		-initialize ClientInfo struct
		-Loop to accept client packets
		-Lock physics engine mutex and call physics engine function to accept
			 client packets, update the physics engine/world state, and send
			 update packet to client (update_world_state(NetPacket packet))
		-Unlock physics engine mutex
		*/
		NetPacket receive_from_client(int client_fd);
		
};

#endif
