#include <iostream>
#include <vector>

#include "../engines/physics/projectile.h"
#include "../classes/ship.h"
#include "netpacket.h"
#include "packetprotos.pb.h"

using namespace std;

void build_ship(Ship *ship) {
	vector<float> pos { 1,2,3 };
	ship->set_d(pos);
	vector<float> vel { 4,5,6 };
	ship->set_v(vel);
	vector<float> accel { 7,8,9 };
	ship->set_a(accel);
		 
	vector<float> pitch { 10,11,12 };
	ship->set_p(pitch);
	vector<float> yaw { 13,14,15 };
	ship->set_y(yaw);
	vector<float> roll { 16,17,18 };
	ship->set_r(roll);
		 
	ship->set_p_dot(6.6);
	ship->set_y_dot(8.8);
	ship->set_r_dot(7.7);
}

int get_packet_type_test() {

	// Build NetPacket
	NetPacket packet;
	protos::GeneralPacket gen_packet;
	Ship ship(1, 1, 2.0, 2.0);
	build_ship(&ship);

	// Build Ship Init Packet
	protos::ShipInitPacket ship_init_packet;
	protos::RenderedObj *ship_packet = ship_init_packet.mutable_ship();
	PacketUtils::fill_obj_packet(ship_packet, &ship);
	string *serialized_ship_init_packet = gen_packet.mutable_packet();
	ship_init_packet.SerializeToString(serialized_ship_init_packet);

	// Build General Packet
	gen_packet.set_packettype(PacketType::SHIP_INIT);
	string serialized_gen_packet;
	gen_packet.SerializeToString(&serialized_gen_packet);
	packet.packet_len = sizeof(int) + sizeof(serialized_gen_packet);
	packet.serialized_packet = serialized_gen_packet;

	// Read from NetPacket
	protos::GeneralPacket parsed_gen_packet;
	if (!parsed_gen_packet.ParseFromString(packet.serialized_packet))
		return 1;
	if (parsed_gen_packet.packettype() != PacketType::SHIP_INIT)
		return 1;
	 
	cout << "get_packet_type test Passed!" << endl;
	return 0;
}

int get_packet_payload_test() {
	// Build NetPacket
	NetPacket packet;
	protos::GeneralPacket gen_packet;
	Ship ship(1, 1, 2.0, 2.0);
	build_ship(&ship);

	// Build Ship Init Packet
	protos::ShipInitPacket ship_init_packet;
	protos::RenderedObj *ship_packet = ship_init_packet.mutable_ship();
	PacketUtils::fill_obj_packet(ship_packet, &ship);
	string *serialized_ship_init_packet = gen_packet.mutable_packet();
	ship_init_packet.SerializeToString(serialized_ship_init_packet);

	// Build General Packet
	gen_packet.set_packettype(PacketType::SHIP_INIT);
	string serialized_gen_packet;
	gen_packet.SerializeToString(&serialized_gen_packet);
	packet.packet_len = sizeof(int) + sizeof(serialized_gen_packet);
	packet.serialized_packet = serialized_gen_packet;

	// Call get_packet_payload on packet
	protos::ShipInitPacket parsed_ship_init_packet;
	PacketUtils::get_packet_payload(packet, (void *) &parsed_ship_init_packet);

	// Read get_packet_payload output
	// (TODO): Do this test with other types of packets (not just objects)
	string serialized_new_ship_packet;
	parsed_ship_init_packet.ship().SerializeToString(&serialized_new_ship_packet);
	string serialized_ship_packet;
	ship_packet->SerializeToString(&serialized_ship_packet);
	if (serialized_ship_packet.compare(serialized_new_ship_packet) != 0)
		return 1;

	cout << "get_packet_payload test Passed!" << endl;
	return 0;
}

int make_packet_test() {

	// Build packet
	Ship ship(1, 1, 2.0, 2.0);
	build_ship(&ship);
	protos::RenderedObj ship_packet;
	PacketUtils::fill_obj_packet(&ship_packet, &ship);
	NetPacket packet;
	PacketUtils::make_packet(&packet, PacketType::SHIP_INIT, (void *) &ship, NULL);

	// Check packet length
	if (packet.packet_len != sizeof(int) + sizeof(packet.serialized_packet))
		return 1;

	// Check general packet contents
	protos::ShipInitPacket parsed_ship_init_packet;
	PacketUtils::get_packet_payload(packet, (void *) &parsed_ship_init_packet);

	// Read get_packet_payload output
	// (TODO): Do this test with other types of packets (not just ship_init packets)
	string serialized_new_ship_packet;
	parsed_ship_init_packet.ship().SerializeToString(&serialized_new_ship_packet);
	string serialized_ship_packet;
	ship_packet.SerializeToString(&serialized_ship_packet);
	if (serialized_ship_packet.compare(serialized_new_ship_packet) != 0)
		return 1;
	protos::RenderedObj ship_obj;
	ship_obj.ParseFromString(serialized_new_ship_packet);
	cout << "make_packet test Passed!" << endl;
	return 0;
}

int fill_obj_packet_test() {
	
	Ship ship(1, 1, 2.0, 2.0);
	build_ship(&ship);
	
	protos::RenderedObj ship_packet;
	PacketUtils::fill_obj_packet(&ship_packet, &ship);
	
	if (ship_packet.id() != (unsigned) ship.get_id())
		return 1;
	if (ship_packet.mass() != (unsigned) ship.get_mass())
		return 1;
	if (ship_packet.cur_tolerance() != ship.get_cur_tolerance())
		return 1;
	if (ship_packet.max_tolerance() != ship.get_max_tolerance())
		return 1;
	// TODO - ADD IS_DESTROYED TEST

	vector<float> pos_vec;
	pos_vec.push_back(ship_packet.pos().x());
	pos_vec.push_back(ship_packet.pos().y());
	pos_vec.push_back(ship_packet.pos().z());
	if (pos_vec != ship.get_d())
		return 1;


	vector<float> vel_vec;
	vel_vec.push_back(ship_packet.vel().x());
	vel_vec.push_back(ship_packet.vel().y());
	vel_vec.push_back(ship_packet.vel().z());
	if (vel_vec != ship.get_v())
		return 1;


	vector<float> accel_vec;
	accel_vec.push_back(ship_packet.accel().x());
	accel_vec.push_back(ship_packet.accel().y());
	accel_vec.push_back(ship_packet.accel().z());
	if (accel_vec != ship.get_a())
		return 1;


	vector<float> pitch_vec;
	pitch_vec.push_back(ship_packet.pitch().x());
	pitch_vec.push_back(ship_packet.pitch().y());
	pitch_vec.push_back(ship_packet.pitch().z());
	if (pitch_vec != ship.get_p())
		return 1;


	vector<float> yaw_vec;
	yaw_vec.push_back(ship_packet.yaw().x());
	yaw_vec.push_back(ship_packet.yaw().y());
	yaw_vec.push_back(ship_packet.yaw().z());
	if (yaw_vec != ship.get_y())
		return 1;


	vector<float> roll_vec;
	roll_vec.push_back(ship_packet.roll().x());
	roll_vec.push_back(ship_packet.roll().y());
	roll_vec.push_back(ship_packet.roll().z());
	if (roll_vec != ship.get_r())
		return 1;

	cout << "fill_obj_packet test Passed!" << endl;
	return 0;
}

int main() {
	int return_val;
	return_val = fill_obj_packet_test();
	return_val = get_packet_type_test();
	return_val = get_packet_payload_test();
	return_val = make_packet_test();
	if (return_val == 1)
		cout << "NET PACKET TEST FAILED!" << endl;
	else
		cout << "NET PACKET TEST PASSED!" << endl;
	return 0;
}
