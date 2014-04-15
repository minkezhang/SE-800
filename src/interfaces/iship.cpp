#include <vector>
#include "../interfaces/idestroyable.cpp"
#include "../interfaces/iweapon.cpp"
#include "../interfaces/ipilot.cpp"

/**
 * all ships directly implement this interface
 */

class IShip : public IDestroyable {
	public:
		virtual int get_render_class();
		virtual std::vector<float> get_a();
		virtual IWeapon *get_weapons();
		virtual int get_weapon_index();

		virtual void set_render_class(int render_class);
		virtual void set_a(std::vector<float> a);
		/* alias pitch() */
		virtual void set_o_dot(float o_dot);

		/* drop the correct weapon */
		virtual void del_weapon(IWeapon *weapon);
		virtual void add_weapon(IWeapon *weapon);
		virtual void set_weapon_index(int index);

	private:
		int render_class;
		std::vector<float> a;		// acceleration
		float o_dot;			// angular velocity about the orientation (pitch) axis o -- o_dot < 0 : clockwise
		IWeapon *weapons;
		int weapon_index;		// current active weapon
		float max_v;			// maximum cruising speed of the ship -- limits set_v() (override function from IProjectile)
		float max_a;			// maximum acceleration of the ship -- limits set_a()
};
