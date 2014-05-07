#include "../engines/physics/projectile.h"
#include "../classes/ship.h"
#include "client.h"
#include "netpacket.h"
#include "packetprotos.pb.h"

#include <iostream>

using namespace std;


void build_ship(Ship *ship) {
	vector<float> pos { 1,2,3 };
	ship->set_d(pos);
	vector<float> vel { 4,5,6 };
	ship->set_v(vel);
	ship->set_a(7.0);
		 
	vector<float> pitch { 10,11,12 };
	ship->set_p(pitch);
	vector<float> yaw { 13,14,15 };
	ship->set_y(yaw);
	vector<float> roll { 16,17,18 };
	ship->set_r(roll);
		 
	ship->set_p_dot(6.6);
	ship->set_r_dot(7.7);
}

int connect_to_server_test() {
	ClientNetUtils clientUtils;
	if (!clientUtils.connect_to_server(6667, "127.0.0.1"))
		return 0;
	clientUtils.close_connection();
	cout << "connect test Passed!" << endl;
	return 1;
}

int send_to_server_test() {
	ClientNetUtils clientUtils;

	// Build packet
	Ship ship(1, 1, 2.0, 2.0);
	build_ship(&ship);
	protos::RenderedObj ship_packet;
	PacketUtils::fill_obj_packet(&ship_packet, &ship);
	cout << "SIZE OF SHIP PACKET " << sizeof(ship_packet) << endl;
	NetPacket packet;

	clientUtils.connect_to_server(6667, "127.0.0.1");
	PacketUtils::make_packet(&packet, PacketType::SHIP_INIT, (void *) &ship, NULL);
	cout << "SIZE OF GEN PACKET " << sizeof(packet.serialized_packet) << endl;
	protos::GeneralPacket gen_packet;
	gen_packet.ParseFromString(packet.serialized_packet);
	protos::ShipInitPacket ship_init_packet;
	ship_init_packet.ParseFromString(gen_packet.packet());
	cout << "SIZE OF SHIP INIT PACKET " << sizeof(ship_init_packet) << endl;
	if (!clientUtils.send_to_server(&packet))
		return 0;
	clientUtils.close_connection();
	cout << "send to server test Passed!" << endl;
	return 1;
}

int main() {
	int return_val = 0;
	return_val += connect_to_server_test();
	return_val += send_to_server_test();

	if (return_val == 2)
		cout << "CLIENT TESTS PASSED" << endl;
	else
		cout << "CLIENT TESTS FAILED" << endl;
}
