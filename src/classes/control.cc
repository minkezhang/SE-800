#include <iostream>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osg/PositionAttitudeTransform>
#include <osg/Material>
#include <osg/StateAttribute>
#include <osg/StateSet>

#include "control.h"
#include "gameaudio.h"
#include "../networks/client.h"
#include "../networks/netpacket.h"
#include "../networks/packetprotos.pb.h"
#include "../engines/physics/projectile.h"
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

ClientControl::UIEventHandler::UIEventHandler(ClientNetUtils* net_utils, GameAudio *audio, osg::PositionAttitudeTransform *main_ship_trans) {
	this->net_utils = net_utils;
	this->audio = audio;
	this->main_ship_trans = main_ship_trans;
	this->is_pressing_accel = false;
	this->is_pressing_brake = false;
	this->is_mouse_move_roll = false;
	this->is_mouse_move_pitch = false;
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
								// Update ship's effusive lighting upon acceleration.
								osg::Material* mat = (osg::Material *) this->main_ship_trans->getStateSet()->getAttribute(osg::StateAttribute::MATERIAL);
								mat->setEmission(osg::Material::FRONT, osg::Vec4(0.25, 0.25, 0.25, 1.0));
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
						if (this->audio != NULL) {
							int action = Action::BULLET_FIRE;
							NetPacket packet;
							PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, NULL);
							if (net_utils->send_to_server(&packet))
								std::cout << "Sent bullet control packet." << std::endl;
							// Play bullet audio (we do this before the bullet is rendered.
							audio->munition_audio(ObjType::BULLET);
						}
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
							// Update ship's effusive lighting upon acceleration.
							osg::Material* mat = (osg::Material *) this->main_ship_trans->getStateSet()->getAttribute(osg::StateAttribute::MATERIAL);
							mat->setEmission(osg::Material::FRONT, osg::Vec4(0, 0, 0, 1.0));
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
				this->is_mouse_move_roll = true;
				NetPacket packet;
				float prev_x = get_prev_x();
				float mouse_x = ea.getXnormalized();
				float bin_x = 0;

				bin_x = ((int) (mouse_x * 100) % 10) * 0.1;

				if (bin_x != prev_x) {
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_x));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent roll tilt control packet." << std::endl;
					prev_x = bin_x;
				}
			}
			{
				int action = Action::PITCH_TILT;
				this->is_mouse_move_pitch = true;
				NetPacket packet;
				float prev_y = get_prev_y();
				float mouse_y = ea.getYnormalized();
				float bin_y = 0;

					bin_y = ((int) (mouse_y * 100) % 10) * 0.1;

				if (bin_y != prev_y) {
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(mouse_y));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent pitch tilt control packet." << std::endl;
					prev_y = bin_y;
				}
			}
				return false;
				break;
		default:
			{
/*
				NetPacket packet;
				float tilt = 0;
				if (this->is_mouse_move_roll) {
					this->is_mouse_move_roll = false;
					int action = Action::RESET_PITCH_TILT;
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(tilt));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent roll tilt control packet." << std::endl;
				}

				if (this->is_mouse_move_pitch) {
					this->is_mouse_move_pitch = false;
					int action = Action::RESET_ROLL_TILT;
					PacketUtils::make_packet(&packet, PacketType::CONTROL_INPUT, (void *) &action, (void *) &(tilt));
					if (net_utils->send_to_server(&packet))
						std::cout << "Sent pitch tilt control packet." << std::endl;
				}
*/
			}
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
	} else if (action == Action::RESET_PITCH_TILT) {
		float *tilt = (float *) action_arg;
		p->toggle_p_dot(obj_id, *tilt);
	} else if (action == Action::ROLL_TILT) {
		float *tilt = (float *) action_arg;
		p->toggle_r_dot(obj_id, *tilt);
	} else if (action == Action::RESET_ROLL_TILT) {
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
