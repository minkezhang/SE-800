#include "../interfaces/imunition.cpp"

class IWeapon {
	public:
		virtual std::string get_name();
		virtual int get_ammo();
		virtual float get_rate();
		virtual IMunition *get_munition();

		/**
		 * creates an instance of the munition and sets instance r and v
		 *
		 * delays in some way the firing if
		 *	current_time - last_fire < rate
		 *
		 * set last to update the last time a munition is fired and decrement ammo
		 */
		virtual void fire();

	private:
		std::string name;
		int ammo;
		float rate;			// minimum time between shots
		float last;			// last time that a munition was fired
		IMunition *munition;
};
