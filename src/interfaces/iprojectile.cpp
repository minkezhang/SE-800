#include <vector>

/**
 * insert comment here :v
 */

class IProjectile {
	public:
		/* delete the object from the world */
		virtual int destroy();
		/* get the (cyclic) position of the object */
		virtual std::vector<float> get_r();
		virtual std::vector<float> get_v();
		virtual std::vector<float> get_d();
		virtual void set_r(std::vector<float> r);
		virtual void set_v(std::vector<float> v);
		virtual void set_d(std::vector<float> d);
	private:
		std::vector<float> r;		// position
		std::vector<float> v;		// velocity
		std::vector<float> d;		// axis of orientation
};
