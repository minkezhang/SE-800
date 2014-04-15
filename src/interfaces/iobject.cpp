#include <vector>
#include "../interfaces/iprojectile.cpp"

class IObject : public IProjectile {
	public:
		virtual int get_id() {
			return(this->id);
		}
		virtual std::vector<float> get_t() {
			return(this->t);
		}
		virtual float get_w() {
			return(this->w);
		}
		virtual float get_mass() {
			return(this->m);
		}
		virtual void set_id(int id) {
			this->id = id;
		}
		virtual void set_t(std::vector<float> t) {
			this->t = t;
		}
		virtual void set_w(float w) {
			this->w = w;
		}
		virtual void set_m(float m) {
			this->m = m;
		}
	private:
		int id;				// unique ID of the object
		std::vector<float> t;		// direction of rotation
		float w;			// rotational velocity -- t_dot > 0 : clockwise
		float m;			// object mass
};
