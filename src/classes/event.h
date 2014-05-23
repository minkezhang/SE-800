#ifndef _EVENT_H
#define _EVENT_H

#include "../engines/physics/projectile.h"

enum EventType {
	DESTROY
};

class Event {
	public:
		Event(Projectile *obj, int event_type);
		int get_id();
		int get_event_type();
    Projectile* obj;

	private:
		int event_type;
};


#endif
