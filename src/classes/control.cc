#include <iostream>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

#include "control.h"
#include "../networks/client.h"
#include "../networks/netpacket.h"
#include "../networks/packetprotos.pb.h"
#include "../engines/physics/physics.h"

float ClientControl::UIEventHandler::get_prev_x() {
	return this->prev_x;
}

float ClientControl::UIEventHandler::get_prev_y() {
	return this->prev_y;
}

void ClientControl::UIEventHandler::set_prev_x(float x) {
	this->prev_x = x;
}

void ClientControl::UIEventHandler::set_prev_y(float y) {
	this->prev_y = y;
}

ClientControl::UIEventHandler::UIEventHandler(ClientNetUtils* net_utils) {
	this->net_utils = net_utils;
	this->is_pressing_accel = false;
	this->is_pressing_brake = false;
	this->prev_x = 0;
	this->prev_y = 0;
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
				float prev_x = get_prev_x();
				float mouse_x = ea.getXnormalized();
				float bin_x = 0;

				if (-0.5 <= mouse_x <= 0.5) {
					bin_x = 0;
				} else if (mouse_x > 0.5) {
					bin_x = ((mouse_x - 0.5) * 2 * 100) % 10) * 0.1;
				} else {
					bin_x = ((mouse_x + 0.5) * 2 * 100) % 10) * 0.1;
				}

				if (bin_x != prev_x) {
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_x));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent roll tilt control packet." << std::endl;
				}
			}
			{
				int action = Action::PITCH_TILT;
				NetPacket packet;
				float prev_y = get_prev_y();
				float mouse_y = ea.getYnormalized();
				float bin_y = 0;

				if (-0.5 <= mouse_y <= 0.5) {
					bin_y = 0;
				} else if (mouse_y > 0.5) {
					bin_y = ((mouse_y - 0.5) * 2 * 100) % 10) * 0.1;
				} else {
					bin_y = ((mouse_y + 0.5) * 2 * 100) % 10) * 0.1;
				}

				if (bix_y != prev_y) {
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_y));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent pitch tilt control packet." << std::endl;
				}
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
-1.0 : -1.0 -> -.95
-0.9 : -0.95 -> -0.90
-0.8 : -0.90 -> -0.85
-0.7 : -0.85 -> -0.80
-0.6 : -0.80 -> -0.75
-0.5 : -0.75 -> -0.70
-0.4 : -0.70 ->
-0.3 :
-0.2 :
-0.1 :
0 : -0.5 -> 0.5
0.1
0.2
*/
}
