#include "cleanup.h"

#include "../physics/projectile.h"

CleanupEngine::CleanupEngine(Environment *environment) : environment(environment) {}

void CleanupEngine::ignite() {}
void CleanupEngine::cycle() {
	while(this->status != STOPPED) {
		std::vector<Projectile *> clippable = this->environment->get_clippable();
		std::vector<Projectile *> unclippable = this->environment->get_unclippable();
		for(unsigned long int i = 0; i < clippable.size(); i++) {
			if(clippable.at(i)->get_is_destroyed()) {
				if(!clippable.at(i)->get_is_processed()) {
					// call server broadcast
					clippable.at(i)->set_is_processed();
				}
			}
		}
		for(unsigned long int i = 0; i < unclippable.size(); i++) {
			if(unclippable.at(i)->get_is_destroyed()) {
				if(!unclippable.at(i)->get_is_processed()) {
					// call server broadcast
					unclippable.at(i)->set_is_processed();
				}
			}
		}
	}
}
void CleanupEngine::shutdown() {
	this->status = STOPPED;
}
