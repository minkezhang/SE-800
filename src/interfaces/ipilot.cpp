#include "../interfaces/iship.cpp"

class IPilot {
	public:
		virtual std::string get_name();
		virtual IGroup *get_group();
		virtual int get_id();

		virtual void set_name(std::string name);
		virtual void set_group(IGroup *group);

		/* called to update the ship trajectory */
		virtual void control();
	private:
		int id;
		std::string name;
		IGroup *group;		// the group of pilots
		IShip *ship;		// the current ship which the pilot is controlling
};
