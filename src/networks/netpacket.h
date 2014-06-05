#ifndef _NETPACKET_H
#define _NETPACKET_H

#include <cstdint>
#include <string>

#include "../engines/physics/projectile.h"
#include "packetprotos.pb.h"

using namespace std;

struct NetPacket {
	int32_t packet_len;
	string serialized_packet;
};

enum PacketType {
	// Packets server can send:
	SHIP_INIT,
	OBJS_AND_EVENTS,
	// Packets client can send:
	CLIENT_INIT,
	EVENT_ACK,
	OBJS_AND_EVENTS_REQ,
	CONTROL_INPUT
};

class PacketUtils {
	public:
		static int get_packet_type(NetPacket packet);
		static void get_packet_payload(NetPacket packet, void* proto_packet);
		static void make_packet(
			NetPacket *packet, PacketType type, void* payload, void* extra_payload);
		static void fill_obj_packet(protos::RenderedObj *obj_packet, Projectile* obj, int type);
};

#endif
