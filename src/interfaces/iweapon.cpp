#include "../interfaces/imunition.cpp"

class IWeapon {
	public:
		virtual std::string get_name();
		virtual int get_ammo();
		virtual float get_rate();

		virtual void fire();
	private:
		std::string name;
		int ammo;
		float rate;			// minimum time between shots
		float last_fire;
		IMunition *munition;
		virtual void set_last_fire(float last_fire);
};
