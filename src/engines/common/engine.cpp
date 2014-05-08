#include "../../../lib/exception.h"

#include "engine.h"

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

int Engine::get_status() {
	return(this->status);
}
