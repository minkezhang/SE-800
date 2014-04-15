class IGroup {
	public:
		virtual ITeam *get_team();
		virtual IPilot *get_pilots();
		virtual int get_id();

		/* returns a member from the group if no leader present */
		virtual IPilot *get_leader();

		virtual void set_team(ITeam *team);

		/* deletes matching pilot from this->members */
		virtual void set_leader(IPilot *pilot);
		virtual void add_member(IPilot *pilot);
		virtual void del_member(IPilot *pilot);
	private:
		int id;
		ITeam *team;
		IPilot *leader;
		IPilot *members;

		/* makes sure the id doesn't collide with any other group ids on the team */
		virtual void set_id(int id);
};
