#include "../interfaces/iprojectile.cpp"

/**
 * bullets and bombs would inherit from tihs interface
 */

class IMunition : public IProjectile {
	public:
		/* guided missiles fly differently than a bullet */
		// virtual void flight_pattern();
		virtual float get_range();
		virtual float set_range();
		virtual int get_render_class();

		/* action to take upon impacting an object */
		virtual void explode();

	private:
		int render_class;
		float range;		// distance the munition can travel
		float aoe;		// area of effect

		/* for ships near the munition at explosion, get damage output */
		virtual void get_damage(float distance);
};
