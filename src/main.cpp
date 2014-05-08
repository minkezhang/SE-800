#include <string.h>
#include <iostream>
#include <thread>

#include "engines/world/world.h"
#include "networks/server.h"

int main(int argc, char **argv) {
	if((argc == 1) || (argc >= 2 && (strcmp(argv[1], "server") && strcmp(argv[1], "client")))) {
		std::cout << "usage: ./... server | client\n";
		exit(0);
	}
	WorldEngine w = WorldEngine();
	// start server / client network
	if(!strcmp(argv[1], "server")) {
		int port = 6667;
		Server s = Server();
		std::thread x (&Server::accept_clients, &s, (void *) &port);
		x.join();
	}
	w.ignite();
	w.cycle();
	w.shutdown();
	return(0);
}
