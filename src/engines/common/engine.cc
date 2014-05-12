#include "../../../lib/exception.h"

#include "engine.h"


int Engine::get_status() { return(this->status); }

int Engine::get_signal() { return(this->signal); }

/**
 * these functions should be not be implemented here
 */
void Engine::ignite() {
	throw BaseClassUnimplementedError();
}

void Engine::cycle() {
	throw BaseClassUnimplementedError();
}

void Engine::shutdown() {
	throw BaseClassUnimplementedError();
}
