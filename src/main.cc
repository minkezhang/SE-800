#include <stdio.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "engines/world/world.h"
#include "engines/physics/physics.h"
#include "networks/server.h"
#include "engines/scheduling/scheduling.h"
#include "engines/scheduling/calendar.h"

void usage(char *exec) {
	std::cout << "usage: " << exec << " ( server < port > | client < port > < ip > )\n";
	exit(0);
}

int main(int argc, char **argv) {
	if(argc < 3) {
		usage(argv[0]);
	} else if((argc == 3) && !strcmp(argv[1], "client")) {
		usage(argv[0]);
	}
	int port = std::stoi(argv[2]);
	SchedulingEngine scheduler = SchedulingEngine();

	if(!strcmp(argv[1], "server")) {
		PhysicsEngine p = PhysicsEngine();
		Calendar cal_p = Calendar(1, &p);
		scheduler.add_calendar(&cal_p);
	} else if(!strcmp(argv[2], "client")) {
	}

	WorldEngine world = WorldEngine(&scheduler);
	std::thread game;

	std::thread network;
	if(!strcmp(argv[1], "server")) {
		// Server server = Server();
		// network = std::thread(&Server::accept_clients, &server, (void *) &port);
	} else if(!strcmp(argv[2], "client")) {
		char *ip = argv[3];
		/*
		ClientNetUtils c = ClientNetUtils();
		c.connect_to_server(port, "127.0.0.1");
		*/
	}

	world.ignite();

	// execute the game
	game = std::thread(&WorldEngine::cycle, &world);

	// wait for the network to shutdown -- probably when clients == 0
	// network.join();

	// end the game
	game.join();

	printf("hi\n");

	world.shutdown();
	return(0);
}
