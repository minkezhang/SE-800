#include "player.h"

Player::Player(std::string name, int socketfd) : Pilot::Pilot(name, 1) {
	this->client_socketfd = socketfd;
}

int Player::get_socketfd() {
	return this->client_socketfd;
}
