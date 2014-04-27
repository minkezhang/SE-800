#include "../../../lib/exception.h"

#include "../engines/common/engine.h"

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
