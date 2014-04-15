#include <vector>
#include "../interfaces/iprojectile.cpp"

/**
 * all steerable objects are derived from this
 *
 * note the difference between
 *	std::vector<float> d : axis of rotation (roll axis)
 *	std::vector<float> o : axis of orientation (pitch axis)
 */

class IObject : public IProjectile {
	public:
		virtual int get_id();
		virtual std::vector<float> get_t();
		virtual float get_w();
		virtual float get_mass();

		virtual void set_id(int id);
		virtual void set_o(std::vector<float> o);
		/* alias roll() */
		virtual void set_d_dot(float d_dot);
		virtual void set_m(float m);

	private:
		int id;
		std::vector<float> o;		// axis of orientation (pitch axis)
		float d_dot;			// rotational velocity about the rotation (roll) axis d -- d_dot > 0 : clockwise
		float m;			// object mass
};
