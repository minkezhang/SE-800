#include "cleanup.h"

#include "../physics/projectile.h"
#include "../../classes/event.h"
#include <algorithm>
#include <mutex>

CleanupEngine::CleanupEngine(Environment *environment) : environment(environment) {}

void CleanupEngine::ignite() {}
void CleanupEngine::cycle() {
	while(this->status != STOPPED) {
		// Do not add more events to event list if clients are in the middle of rendering event list.
		if (this->processed_clientfds.size() > 0)
			continue;
		std::vector<Projectile *> clippable = this->environment->get_clippable();
		std::vector<Projectile *> unclippable = this->environment->get_unclippable();
		for(unsigned long int i = 0; i < clippable.size(); i++) {
			if(clippable.at(i)->get_is_destroyed()) {
				if(!clippable.at(i)->get_is_processed()) {
					std::vector<int> id_and_type = { clippable.at(i)->get_id(), EventType::DESTROY };
					if (this->event_list.count(id_and_type) == 0) {
						Event *event = new Event(clippable.at(i), EventType::DESTROY);
						this->event_list_lock.lock();
						this->event_list[id_and_type] = event;
						this->event_list_lock.unlock();
					}
				}
			}
		}
		for(unsigned long int i = 0; i < unclippable.size(); i++) {
			if(unclippable.at(i)->get_is_destroyed()) {
				if(!unclippable.at(i)->get_is_processed()) {
					std::vector<int> id_and_type = { unclippable.at(i)->get_id(), EventType::DESTROY };
					// Add event to event list if not already there.
					if (this->event_list.count(id_and_type) == 0) {
						Event *event = new Event(unclippable.at(i), EventType::DESTROY);
						this->event_list_lock.lock();
						this->event_list[id_and_type] = event;
						this->event_list_lock.unlock();
					}
				}
			}
		}
	}
}

std::vector<Event *> CleanupEngine::send_event_vec(int clientfd, int num_clients) {
	std::vector<Event *> events = {};
	if (this->event_list.size() == 0)
		return events;
	// If client has already processed events, do not send them again
	if (std::find(this->processed_clientfds.begin(), this->processed_clientfds.end(), clientfd) != this->processed_clientfds.end())
		return events;

	this->event_list_lock.lock();
	for (std::map<std::vector<int>, Event *>::iterator i = this->event_list.begin(); i != this->event_list.end(); ++i) {
		events.push_back((*i).second);
		(*i).second->obj->set_is_processed();
	}
	this->processed_clientfds.push_back(clientfd);
	// If all clients have rendered events, clear new events list
	if (this->processed_clientfds.size() == (unsigned) num_clients) {
		for (std::map<std::vector<int>, Event *>::iterator i = this->event_list.begin(); i != this->event_list.end(); ) {
			i = this->event_list.erase(i);
		}
		for (std::list<int>::iterator i = this->processed_clientfds.begin(); i != this->processed_clientfds.end(); ) {
			i = this->processed_clientfds.erase(i);
		}
	}
	this->event_list_lock.unlock();
	return events; 
}

void CleanupEngine::shutdown() {
	this->status = STOPPED;
}


