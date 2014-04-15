#include <vector>
#include "../interfaces/idestroyable.cpp"
#include "../interfaces/iweapon.cpp"
#include "../interfaces/ipilot.cpp"

class IShip : public IDestroyable {
	public:
		virtual int get_render_class() {
			return(this->render_class);
		}
		virtual std::vector<float> get_a() {
			return(this->a);
		}
		virtual float get_phi_dot() {
			return(this->phi_dot);
		}
		virtual IWeapon *get_weapons() {
			return(this->weapons);
		}
		virtual int get_weapon_index() {
			return(this->weapon_index);
		}
		virtual void set_render_class(int render_class) {
			this->render_class = render_class;
		}
		virtual void set_a(std::vector<float> a) {
			this->a = a;
		}
		virtual void set_phi_dot(float phi_dot) {
			this->phi_dot = phi_dot;
		}
		virtual void add_weapon(IWeapon *weapon);

		/* drop the correct weapon */
		virtual void drop_weapon(int index);
		virtual void set_weapon_index(int index) {
			this->weapon_index = index;
		}
	private:
		int render_class;
		std::vector<float> a;		// acceleration
		float phi_dot;			// rotation of the axis of rotation

		IWeapon *weapons;
		int weapon_index;		// current active weapon
};
