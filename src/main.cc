#include <stdio.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <pthread.h>

#include "engines/world/world.h"
#include "engines/physics/physics.h"
#include "engines/graphics/graphics.h"
#include "networks/server.h"
#include "networks/client.h"
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

	// create empty world and schedule
	SchedulingEngine scheduler = SchedulingEngine();
	WorldEngine world = WorldEngine(&scheduler);
	std::thread game;
	std::thread network;

	// engines to start with associated calendars
	//	declare here to preserve scoping
	PhysicsEngine *p;
	GraphicsEngine *g;
	Calendar *cal_p;
	Calendar *cal_g;
	ClientNetUtils *c;

	GraphicsEngine *g;
	Calendar *cal_g;

	if(!strcmp(argv[1], "server")) {
		Server *server = new Server(&world);
		network = std::thread(&Server::accept_clients, server, (void *) &port);

		p = new PhysicsEngine();
		cal_p = new Calendar(100, p);
		scheduler.add_calendar(cal_p);

	} else if(!strcmp(argv[1], "client")) {
		string ip(argv[3]);
		g = new GraphicsEngine();
<<<<<<< HEAD
		ClientNetUtils *c = new ClientNetUtils(&g->packet_que, &g->que_lock);
=======
		c = new ClientNetUtils(&g->packet_que, &g->que_lock);
>>>>>>> 760d8f1b1c56fe79d13bc6e0a5375ae7c4f91aba

		if (!c->connect_to_server(port, ip)) {
			std::cout << "Could not connect to server. Exiting." << std::endl;
			exit(1);
		}
<<<<<<< HEAD
		network = std::thread(&ClientNetUtils::receive_from_server, c);

		g->net_utils = c;
		g->ignite();
=======
		if (pthread_create(&receive_packet_thread, NULL, ClientNetUtils::receive_from_server, &c->server_sockfd) != 0) {
			std::cout << "Could not create a worker thread. Exiting." << std::endl;
			exit(1);
		}
>>>>>>> 760d8f1b1c56fe79d13bc6e0a5375ae7c4f91aba

		cal_g = new Calendar(1, g);
		scheduler.add_calendar(cal_g);

		g->ignite();
		g->net_utils = c;
	}

	world.ignite();

	// execute the game
	game = std::thread(&WorldEngine::cycle, &world);

	// wait for the network to shutdown -- probably when clients == 0
	network.join();

	// end the game
	game.join();

	world.shutdown();
	return(0);
}
