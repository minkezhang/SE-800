#ifndef _PLAYER_H
#define _PLAYER_H

#include "pilot.h"
#include <string>

class Player;

class Player : public Pilot {
	public:
		Player(std::string name, int socketfd);
		int get_socketfd();

	private:
		int client_socketfd;
};

#endif
