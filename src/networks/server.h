#ifndef _SERVER_H
#define _SERVER_H

#include <map>

#include "netpacket.h"

using namespace std;

class Server {
	public:
		
		/* server constructor actions: 
		-initialize Physics Engine object
		-spawn worker thread to accept clients
		-wait until at least one client has connected
		-start world engine & scheduler
		*/
		Server(int port);
		~Server();
		int get_client_fd(int id);
		bool send_to_client(NetPacket *packet, int client_id);
    static void *serve_client(void *args);

	private:
		map<int, int> client_id_to_fd;
		//PhysicsEngine *physics_engine;
    int server_socketfd;
	
		/* accept_clients actions:
		-client connections, spawning a thread for each connection */
		void *accept_clients(void *args);
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