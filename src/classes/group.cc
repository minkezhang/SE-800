#include <vector>
#include "../classes/group.h"

int GROUP_COUNT = 0;

Group::Group(Team *team){
    this->id = GROUP_COUNT;				// set in constructor
		GROUP_COUNT++;
    this->team = team;
    this->leader = NULL;
}

Team *Group::get_team(){
    return this->team;
}
int Group::get_id(){
    return this->id;
}
/**
* returns a escort from the group if no leader present (invoke select_leader)
*
* should never return NULL
*/
Pilot *Group::get_leader(){
    if (this->leader!=NULL){
        return this->leader;
    }
    else{
        if(this->escorts.size() > 0){
						set_leader(this->escorts.at(0));
						return this->leader;
        }
        else{
            return NULL;
        }
    }
}

/* deletes matching pilot from this->escorts (if such a pilot exists) -- may need to call select_leader to find suitable candidate */
void Group::set_leader(Pilot *pilot){
		if (pilot) {
			del_escort(pilot);
			this->leader = pilot;
		} else {
			//TODO: Flesh out destructor
//			~Group();
		}
}
void Group::del_leader(){
    set_leader(select_leader());
}// on ship destroy, reset and get new leader

		/* escort cannot be the current leader */
void Group::add_escort(Pilot *pilot){
    if (this->leader.get_id()!=pilot.get_id){
        this->escorts.push_back(pilot);
    }
}
void Group::del_escort(Pilot *pilot){
		// TODO : PASS IN ID OF PILOT
    this->escorts.remove(pilot);
}

Pilot *Group::select_leader(){
    if(this->escorts.size() > 0){
        return escorts.at(0);
    } else
			return NULL;
}
