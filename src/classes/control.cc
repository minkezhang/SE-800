#include <iostream>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

#include "control.h"
#include "../networks/client.h"
#include "../networks/netpacket.h"
#include "../networks/packetprotos.pb.h"

ClientControl::UIEventHandler::UIEventHandler(ClientNetUtils* net_utils) {
	this->net_utils = net_utils;
}

bool ClientControl::UIEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&) {
	switch(ea.getEventType()) {
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				switch(ea.getKey()) {
					case osgGA::GUIEventAdapter::KEY_Up:
					{
						int action = Action::ACCEL;
						NetPacket packet;
						PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
						if (net_utils->send_to_server(&packet))
							std::cout << "Sent accel control packet." << std::endl;
					}
						return false;
						break;
					case osgGA::GUIEventAdapter::KEY_Down:
					{
						int action = Action::BRAKE;
						NetPacket packet;
						PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
						if (net_utils->send_to_server(&packet))
							std::cout << "Sent brake control packet." << std::endl;
					}
						return false;
						break;
					case osgGA::GUIEventAdapter::KEY_Space:
					{
						int action = Action::BULLET;
						NetPacket packet;
						PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
						if (net_utils->send_to_server(&packet))
							std::cout << "Sent bullet control packet." << std::endl;
					}
						return false;
						break;
					default:
						return false;
				}
			}
		case(osgGA::GUIEventAdapter::MOVE):
			{
				std::cout << "X IS " << ea.getXnormalized() << std::endl;
				std::cout << "Y IS " << ea.getYnormalized() << std::endl;
				return false;
				break;
			}
		default:
			return false;
	}
}

void ClientControl::UIEventHandler::accept(osgGA::GUIEventHandlerVisitor& v) {
	v.visit(*this);
}

void ServerControl::update_physics(protos::ControlInput control) {
}
