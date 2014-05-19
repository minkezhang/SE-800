#ifndef _UICONTROL_H
#define _UICONTROL_H

#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

#include "../networks/client.h"
#include "../networks/packetprotos.pb.h"
#include "../engines/physics/physics.h"

enum Action {
	ACCEL,
	BRAKE,
	RESET_ACCEL,
	ROLL_TILT,
	PITCH_TILT,
	BULLET,
	MISSILE,
	BOMB,
	SPEC_POWERUP
};

class ClientControl {
	public:
		class UIEventHandler : public osgGA::GUIEventHandler {
			public:
				UIEventHandler(ClientNetUtils *net_utils);
				virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
				virtual void accept(osgGA::GUIEventHandlerVisitor& v);
			private:
				ClientNetUtils *net_utils;
				bool is_pressing_accel;
				bool is_pressing_brake;
		};
};

class ServerControl {
	public:
		static void update_physics(int obj_id, int action, void *action_arg, PhysicsEngine *p);
};

#endif
