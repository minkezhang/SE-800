#include <string.h>
#include <iostream>
#include <thread>

#include "engines/world/world.h"
#include "networks/server.h"

int main(int argc, char **argv) {
	if((argc < 3) || (argc >= 2 && (strcmp(argv[1], "server") && strcmp(argv[1], "client")))) {
		std::cout << "usage: ./... server | client < port >\n";
		exit(0);
	}
	int port = 6667; // std::stoi(argv[3]);
	WorldEngine w = WorldEngine();
	// start server / client network
	std::thread network;
	if(!strcmp(argv[1], "server")) {
		Server s = Server();
		network = std::thread(&Server::accept_clients, &s, (void *) &port);
	}
	network.join();
	/*
	else if(!strcmp(argv[2], "client")) {
		ClientNetUtils c = ClientNetUtils();
		c.connect_to_server(port, "127.0.0.1");
	}*/
	w.ignite();
	w.cycle();
	w.shutdown();
	return(0);
}
