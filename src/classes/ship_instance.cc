#include "ship_instance.h"

ShipCarrier::ShipCarrier(int id, std::vector<float> d) : Ship(id, 1000, 400, d, 9.5, 100, 2, 2) {}
ShipScout::ShipScout(int id, std::vector<float> d) : Ship(id, 200, 100, d, .2, 500, .5, .5) {}
ShipFighter::ShipFighter(int id, std::vector<float> d) : Ship(id, 400, 200, d, .4, 200, .5, .5) {}
