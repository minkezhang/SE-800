#ifndef _CONTROL_H
#define _CONTROL_H

#include "../networks/packetprotos.pb.h"

enum Action {
	ACCEL,
	BRAKE,
	ROLL_TILT,
	PITCH_TILT,
	BULLET,
	MISSILE,
	BOMB,
	SPEC_POWERUP
};

class Control {
	public:
		static update_physics(protos::ControlInput control);
};

#endif
