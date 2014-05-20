#ifndef _SHIP_INSTANCE_H
#define _SHIP_INSTANCE_H

#include <vector>

#include "ship.h"

class ShipCarrier : public Ship {
	public:
		ShipCarrier(int id, std::vector<float> d);
};

class ShipScout : public Ship {
	public:
		ShipScout(int id, std::vector<float> d);
};

class ShipFighter : public Ship {
	public:
		ShipFighter(int id, std::vector<float> d);
};

#endif
