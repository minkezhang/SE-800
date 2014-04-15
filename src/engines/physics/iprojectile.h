#ifndef _IPROJECTILE_H
#define _IPROJECTILE_H

/**
 * base interface for all objects which needs to be simulated
 */

#include <vector>

class IProjectile {
	public:
		int get_id();
		int get_size();

		std::vector<float> get_d();
		std::vector<float> get_v();
		std::vector<float> get_a();

		std::vector<float> get_p();
		std::vector<float> get_y();
		std::vector<float> get_r();

		float get_p_dot();
		float get_y_dot();
		float get_r_dot();

		std::vector<float> set_d();
		std::vector<float> set_v();
		std::vector<float> set_a();

		std::vector<float> set_p();
		std::vector<float> set_y();
		std::vector<float> set_r();

		float set_p_dot();
		float set_y_dot();
		float set_r_dot();

	private:
		int id;
		int size;

		/* positional-related vectors */
		std::vector<float> d;
		std::vector<float> v;
		std::vector<float> a;

		/* pitch, yaw, roll vectors */
		std::vector<float> p;
		std::vector<float> y;
		std::vector<float> r;

		float p_dot;
		float y_dot;
		float r_dot;
};

#endif
