#include "event.h"

Event::Event(int id, int event_type) : id(id), event_type(event_type) {
}

int Event::get_id() {
	return this->id;
}

int Event::get_event_type() {
	return this->event_type;
}
