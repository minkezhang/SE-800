#ifndef _NETPACKET_H
#define _NETPACKET_H

#include <cstdint>

#include "packetprotos.pb.h"

class PacketUtils {
	public:
		enum PacketType {
			// Packets server can send:
			SHIP_INIT,
			OBJS_AND_EVENTS,
			// Packets client can send:
			EVENT_ACK,
			CONTROL_INPUT
		};

		static struct NetPacket {
			int32_t packet_len;
			string serialized_packet;
		};
	
		static PacketType get_packet_type(NetPacket packet);
		template<typename PACKET_PROTO>
		static PACKET_PROTO get_packet_payload(NetPacket packet);
		template<typename PAYLOAD_TYPE>
		static NetPacket make_packet(PacketType type, PAYLOAD_TYPE payload);
};

#endif
