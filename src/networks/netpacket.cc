#include <cstdint>

#include "packetprotos.pb.h"

static PacketUtils::PacketType PacketUtils::get_packet_type(
	PacketUtils::NetPacket packet) {
	protos::GeneralPacket gen_packet;
	if (!gen_packet.ParseFromString(&(packet.serialized_packet))) {
		cerr << "Failed to parse general proto buffer." << endl;
	} else {
		return gen_packet.packetType();
	}
}

template<typename PACKET_PROTO>
static PACKET_PROTO* PacketUtils::get_packet_payload(
	PacketUtils::NetPacket packet) {
	protos::GeneralPacket gen_packet;
        PacketUtils::PacketType type;
	if (!gen_packet.ParseFromString(&(packet.serialized_packet))) {
		cerr << "Failed to parse general proto buffer." << endl;
		return NULL;
	} else {
		type = gen_packet.packetType();
	}
	if (type == PacketUtils::PacketType::SHIP_INIT) {
		protos::ShipInitPacket* ship_init_packet.New();
		if (!ship_init_packet->ParseFromString(gen_packet.packet())) {
			cerr << "Failed to parse ship init packet." << endl;
			return NULL;
		} else {
			return ship_init_packet;
		}
	} else if (type == PacketUtils::PacketType::OBJS_AND_EVENTS) {
		protos::ObjsAndEventsPacket* objs_and_events_packet.New();
		if (!objs_and_events_packet->ParseFromString(gen_packet.packet())) {
			cerr << "Failed to parse objs and events packet." << endl;
			return NULL;
		} else {
			return objs_and_events_packet;
		}	
	} else if (type == PacketUtils::PacketType::EVENT_ACK) {
		protos::EventAckPacket* event_ack_packet.New();
		if (!event_ack_packet->ParseFromString(gen_packet.packet())) {
			cerr << "Failed to parse event ack packet." << endl;
			return NULL;
		} else {
			return event_ack_packet;
		}
	} else if (type == PacketUtils::PacketType::CONTROL_INPUT) {
		protos::ControlInputPacket* control_input_packet.New();
		if (!control_input_packet->ParseFromString(gen_packet.packet())) {
			cerr << "Failed to parse control input packet." << endl;
			return NULL;
		} else {
			return control_input_packet;
		}
	} else {
		cerr << "Incorrect packet type parsed." << endl;
		return NULL;
	}
}

template<typename PAYLOAD_TYPE>
static PacketUtils::NetPacket* PacketUtils::make_packet(
	PacketUtils::PacketType type, PAYLOAD_TYPE* payload) {
	proto::GeneralPackage gen_package;
	string serialized_packet;

	if (type == PacketUtils::PacketType::SHIP_INIT) {
		Ship* ship = (Ship *) payload;
		protos::RenderedObj ship_package;
		ship_package.set_id(ship->get_id());
		ship_package.set_mass(ship->get_mass());
		ship_package.set_cur_tolerance(ship->get_cur_tolerance());
		ship_package.set_max_tolerance(ship->get_max_tolerance());
		ship_package.set_is_destroyed(ship->is_destroyed());

		protos::vector pos_vector;
		pos_vector.set_x(ship->get_d().at(0));
		pos_vector.set_y(ship->get_d().at(1));
		pos_vector.set_z(ship->get_d().at(2));
		ship_package.set_allocated_pos(&pos_vector);

		protos::vector vel_vector;
		vel_vector.set_x(ship->get_v().at(0));
		vel_vector.set_y(ship->get_v().at(1));
		vel_vector.set_z(ship->get_v().at(2));
		ship_package.set_allocated_vel(&vel_vector);

		protos::vector accel_vector;
		accel_vector.set_x(ship->get_a().at(0));
		accel_vector.set_y(ship->get_a().at(1));
		accel_vector.set_z(ship->get_a().at(2));
		ship_package.set_allocated_accel(&accel_vector);

		protos::vector pitch_vector;
		pitch_vector.set_x(ship->get_p().at(0));
		pitch_vector.set_y(ship->get_p().at(1));
		pitch_vector.set_z(ship->get_p().at(2));
		ship_package.set_allocated_pitch(&pitch_vector);

		protos::vector roll_vector;
		roll_vector.set_x(ship->get_r().at(0));
		roll_vector.set_y(ship->get_r().at(1));
		roll_vector.set_z(ship->get_r().at(2));
		ship_package.set_allocated_roll(&roll_vector);

		protos::vector yaw_vector;
		yaw_vector.set_x(ship->get_y().at(0));
		yaw_vector.set_y(ship->get_y().at(1));
		yaw_vector.set_z(ship->get_y().at(2));
		ship_package.set_allocated_yaw(&yaw_vector);
		ship_package.set_weapon_index(ship->get_weapon_index());

		if (!ship_package.SerializeToString(&serialized_packet)) {
			cerr << "Could not serialize ship package to string." << endl;
			return NULL;
		}

	} else if (type == PacketUtils::PacketType::OBJS_AND_EVENTS) {
		// FUCK		
	} else if (type == PacketUtils::PacketType::EVENT_ACK) {
		int *ack = (int *) payload;
		proto::EventAckPacket event_ack_packet;
		proto::GeneralPacket gen_packet;
		event_ack_packet.set_ack(*ack);

		if (!event_ack_packet.SerializeToString(&serialized_packet)) {
			cerr << "Could not serialize event ack package to string." << endl;
			return NULL;
		}
		
	} else if (type == PacketUtils::PacketType::CONTROL_INPUT) {
		//(TODO): fill in when control interface is done.
	} else {
		cerr << "Incorrect type argument specified." << endl;
		return NULL;
	}

	// Construct General packet
	gen_packet.set_type(type);
	gen_packet.set_packet(serialized_packet);

	string serialized_gen_packet;
	if (!gen_packet.SerializeToString(&serialized_gen_packet)) {
		cerr << "Could not serialize gen packet to string." << endl;
		return NULL;
	}

	// Construct final packet
	int packet_size = sizeof(uint32_t) + sizeof(serialized_gen_packet);
	PacketUtils::NetPacket *final_packet = (PacketUtils::NetPacket *)
		malloc(packet_size);
	final_packet->packet_len = packet_size;
	memcpy((void *) &(final_packet->serialized_packet), (void *) &(serialized_gen_packet), sizeof(serialized_gen_packet));
	return final_packet;
}
