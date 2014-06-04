#include "team.h"

int TEAM_COUNT = 0;

Team::Team(){
    this->id = TEAM_COUNT;
    this->groupNum = 0;
    TEAM_COUNT++;
}

int Team::get_id() { return(this->id); }

std::vector<Group> Team::get_groups() { return(this->groups); }

int Team::get_groupNum(){
    return this->groupNum;
}

void Team::add_group(Group *group){
    //Needs mutex?
		this->groups.push_back(*group);
    this->groupNum++;
}

void Team::del_group(Group *group){
    //needs mutex?
//		this->groups.erase(/*TODO GIVE GROUP ID*/);
    this->groupNum--;
}
