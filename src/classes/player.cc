#include "player.h"

Player::Player(std::string name, int socketfd) : Pilot::Pilot(name) {
	this->client_socketfd = socketfd;
}

int Player::get_socketfd() {
	return this->client_socketfd;
}
