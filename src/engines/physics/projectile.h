#ifndef _PROJECTILE_H
#define _PROJECTILE_H

/**
 * base interface for all objects which needs to be simulated
 */

#include <vector>

class Projectile {
	public:
		Projectile(int id, int clippable, float mass, float max_tolerance);

		/**
		 * public-facing functions which can be freely queried
		 */

		int get_id();				// get projectile ID
		int get_size();				// get size
		int get_mass();				// get mass

		float get_cur_tolerance();		// get current health
		float get_max_tolerance();		// get max health
		int is_destroyed();			// return cur_health < 0
		int is_clippable();			// returns if the object is clippable OR if object is destroyed

		std::vector<float> get_d();		// get position
		std::vector<float> get_v();		// get velocity
		float get_a();				// get acceleration

		std::vector<float> get_p();		// get pitch axis
		std::vector<float> get_y();             // get yaw axis
		std::vector<float> get_r();		// get roll axis
		std::vector<float> get_y();		// get yaw axis

		float get_p_dot();			// get pitch rotation speed (x < 0 => counterclockwise)
		float get_y_dot();			// get yaw rotation speed
		float get_r_dot();			// get roll rotation speed

		/**
		 * the following should not be called outside the physics engine
		 */

		void set_d(std::vector<float> d);	// set position
		void set_v(std::vector<float> v);	// set velocity
		void set_a(float a);	// set acceleration

		void set_p(std::vector<float> p);	// set pitch axis
		void set_y(std::vector<float> y);	// set yaw axis
		void set_r(std::vector<float> r);	// set roll axis
		void set_y(std::vector<float> y); 	// set yaw axis

		void set_p_dot(float p_dot);		// set pitch rotation speed
		void set_y_dot(float y_dot);		// set yaw rotation speed
		void set_r_dot(float r_dot);		// set roll rotation speed

		void damage(float tolerance);		// decrement the object tolerance by the input

	private:
		int id;					// global unique ID -- set on construction
		int destroyed;
		int clippable;				// clippable objects do not check for collision with other clippable objects

		float mass;				// mass of object -- set on construction
		float size;				// collision radius

		float cur_tolerance;			// current health -- initialized to max_tolerance
		float max_tolerance;			// max health -- set on construction

		/* positional-related vectors */
		std::vector<float> d;
		std::vector<float> v;
		float a;

		/* pitch, yaw, roll vectors */
		std::vector<float> p;
		std::vector<float> y;
		std::vector<float> r;
		std::vector<float> y;

		float p_dot;
		float y_dot;
		float r_dot;
};

#endif
