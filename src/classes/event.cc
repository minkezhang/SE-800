#include "event.h"
#include "../engines/physics/projectile.h"

Event::Event(Projectile *obj, int event_type) : obj(obj), event_type(event_type) {
}

int Event::get_id() {
	return this->obj->get_id();
}

int Event::get_event_type() {
	return this->event_type;
}
