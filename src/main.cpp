#include <string.h>
#include <iostream>

#include "engines/world/world.h"

int main(int argc, char **argv) {
	if((argc == 1) || (argc >= 2 && (strcmp(argv[1], "server") && strcmp(argv[1], "client")))) {
		std::cout << "usage: ./... server | client\n";
		exit(0);
	}
	WorldEngine w = WorldEngine();
	w.ignite();
	w.cycle();
	w.shutdown();
	return(0);
}
