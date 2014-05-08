#include "engines/world/world.h"

int main() {
	WorldEngine w = WorldEngine();
	w.ignite();
	w.cycle();
	w.shutdown();
	return(0);
}
