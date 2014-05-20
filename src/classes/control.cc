#include <iostream>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

#include "control.h"
#include "../networks/client.h"
#include "../networks/netpacket.h"
#include "../networks/packetprotos.pb.h"
#include "../engines/physics/physics.h"

ClientControl::UIEventHandler::UIEventHandler(ClientNetUtils* net_utils) {
	this->net_utils = net_utils;
	this->is_pressing_accel = false;
	this->is_pressing_brake = false;
}

bool ClientControl::UIEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&) {
	switch(ea.getEventType()) {
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				switch(ea.getKey()) {
					case osgGA::GUIEventAdapter::KEY_Up:
					{
						if (this->is_pressing_accel == false) {
							this->is_pressing_accel = true;
							int action = Action::ACCEL;
							NetPacket packet;
							PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
							if (net_utils->send_to_server(&packet))
								std::cout << "Sent accel control packet." << std::endl;
						}
					}
						return false;
						break;
					case osgGA::GUIEventAdapter::KEY_Down:
					{
						if (this->is_pressing_brake == false) {
							this->is_pressing_brake = true;
							int action = Action::BRAKE;
							NetPacket packet;
							PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
							if (net_utils->send_to_server(&packet))
								std::cout << "Sent brake control packet." << std::endl;
						}
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
		case(osgGA::GUIEventAdapter::KEYUP):
			{
				switch(ea.getKey()) {
					case osgGA::GUIEventAdapter::KEY_Up:
					case osgGA::GUIEventAdapter::KEY_Down:
					{
						this->is_pressing_accel = false;
						this->is_pressing_brake = false;
						int action = Action::RESET_ACCEL;
						NetPacket packet;
						PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
						if (net_utils->send_to_server(&packet))
							std::cout << "Sent reset acceleration control packet." << std::endl;
					}
						return false;
						break;
					default:
						return false;
				}
			}
		case(osgGA::GUIEventAdapter::MOVE):
			{
				int action = Action::ROLL_TILT;
				NetPacket packet;
				float mouse_x = ea.getXnormalized();
				PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_x));
				if (net_utils->send_to_server(&packet))
					std::cout << "Sent roll tilt control packet." << std::endl;
			}
			{
				int action = Action::PITCH_TILT;
				NetPacket packet;
				float mouse_y = ea.getYnormalized();
				PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_y));
				if (net_utils->send_to_server(&packet))
					std::cout << "Sent pitch tilt control packet." << std::endl;
			}
				return false;
				break;
		default:
			return false;
	}
}

void ClientControl::UIEventHandler::accept(osgGA::GUIEventHandlerVisitor& v) {
	v.visit(*this);
}

void ServerControl::update_physics(int obj_id, int action, void *action_arg, PhysicsEngine *p) {
	if (action == Action::ACCEL) {
		p->toggle_a(obj_id, 1);
	} else if (action == Action::RESET_ACCEL) {
		p->toggle_a(obj_id, 0);
	} else if (action == Action::BRAKE) {
		p->toggle_a(obj_id, -1);
	} else if (action == Action::ROLL_TILT) {
		float *tilt = (float *) action_arg;
		p->toggle_r_dot(obj_id, *tilt);
	} else if (action == Action::PITCH_TILT) {
		float *tilt = (float *) action_arg;
		p->toggle_p_dot(obj_id, *tilt);
	} else if (action == Action::ROLL_TILT) {
		float *tilt = (float *) action_arg;
		p->toggle_r_dot(obj_id, *tilt);
	}
/*
	} else if (action == Roll::R_DOT) {
		p->toggle_rdot(obj_id, 1.0)
	//TODO: Add rotation updates
	if (-0.5 < y_posn < 0.5) {
		pitch_val = 0;
	} else if {
		1.0 -> 1.0
		0.5 -> 0.0
		0.6 -> 0.2
	  0.7 -> 0.4
 		-1.0 -> -1.0
		-0.5 -> 0.0
		-0.6 -> -0.2
*/
}
