#include "../interfaces/iprojectile.cpp"

/**
 * bullets and bombs would inherit from tihs interface
 */

class IMunition : public IProjectile {
	public:
		// virtual void flight_pattern();
		virtual float get_range();
		virtual float set_range();
		virtual int get_render_class();

		/* action to take upon impacting an object */
		virtual void explode(float distance);
	private:
		int render_class;
		float range;
};
