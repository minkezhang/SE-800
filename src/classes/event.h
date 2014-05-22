#ifndef _EVENT_H
#define _EVENT_H

enum EventType {
	DESTROY
};

class Event {
	public:
		Event(int id, int event_type);
		int get_id();
		int get_event_type();

	private:
		int id;		// id of the object which event affects
		int event_type;
};


#endif
