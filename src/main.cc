#include <string.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "engines/world/world.h"
#include "networks/server.h"

int main(int argc, char **argv) {
	if((argc < 3) || (argc >= 2 && (strcmp(argv[1], "server") && strcmp(argv[1], "client")))) {
		std::cout << "usage: " << argv[0] << " ( server < port > | client < port > < ip > )\n";
		exit(0);
	}
	int port = std::stoi(argv[2]);
	WorldEngine w = WorldEngine();
	// start server / client network
	std::thread network;
	std::thread game;
	if(!strcmp(argv[1], "server")) {
		Server s = Server();
		network = std::thread(&Server::accept_clients, &s, (void *) &port);
	}
	else if(!strcmp(argv[2], "client")) {
		// char *ip = argv[4];
		/*
		ClientNetUtils c = ClientNetUtils();
		c.connect_to_server(port, "127.0.0.1");
		*/
	}
	w.ignite();
	game = std::thread(&WorldEngine::cycle, &w);
	network.join();
	game.join();
	w.shutdown();

	return(0);
}
