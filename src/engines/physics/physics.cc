#include "physics.h"

using namespace std;

// public
PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::toggle_a(int id, int val) {
	Projectile *p = this->environment->get_projectile(id);
	p->set_a(val * p->get_preset_a());
}

void PhysicsEngine::toggle_p_dot(int id, float val) {
	Projectile *p = this->environment->get_projectile(id);
	p->set_p_dot(val * p->get_preset_p_dot());
}

void PhysicsEngine::toggle_r_dot(int id, float val) {
	Projectile *p = this->environment->get_projectile(id);
	p->set_r_dot(val * p->get_preset_r_dot());
}

// Assumes unit vectors for roll, pitch, and yaw
void PhysicsEngine::apply_rotation(float angle, int flag, Projectile *p) {
	// Precompute sine and cosine
	float cost = cos(angle);
	float sint = sin(angle);
	// Read in vectors from projectile
	vector<float> rol = p->get_r();
	vector<float> pit = p->get_p();
	vector<float> yaw = p->get_y();
	// Initialize terms
	float x = pit.at(0);
	float y = pit.at(1);
	float z = pit.at(2);
	float a = yaw.at(0);
	float b = yaw.at(1);
	float c = yaw.at(2);
	float u = rol.at(0);
	float v = rol.at(1);
	float w = rol.at(2);
	// If flag = 1, rotate around roll axis; else, rotate around pitch axis.
	if (flag == 0) {
		// Rotate pitch axis around roll by angle
		float term_c1 = (u*x + v*y + w*z)*(1 - cost);
		pit.at(0) = u*term_c1 + x*cost + (v*z - w*y)*sint;
		pit.at(1) = v*term_c1 + y*cost + (w*x - u*z)*sint;
		pit.at(2) = w*term_c1 + z*cost + (u*y - v*x)*sint;
		// Rotate yaw axis around roll by angle
		float term_c2 = (u*a + v*b + w*c)*(1 - cost);
		yaw.at(0) = u*term_c2 + a*cost + (v*c - w*b)*sint;
		yaw.at(1) = v*term_c2 + b*cost + (w*a - u*c)*sint;
		yaw.at(2) = w*term_c2 + c*cost + (u*b - v*a)*sint;
	} else {
		// Rotate roll axis around pitch axis by angle
		float term_c1 = (x*u + y*v + z*w)*(1 - cost);
		rol.at(0) = x*term_c1 + u*cost + (y*w - z*v)*sint;
		rol.at(1) = y*term_c1 + v*cost + (z*u - x*w)*sint;
		rol.at(2) = z*term_c1 + w*cost + (x*v - y*u)*sint;
		// Rotate yaw axis around pitch axis by angle
		float term_c2 = (x*a + y*b + z*c)*(1 - cost);
		yaw.at(0) = x*term_c2 + a*cost + (y*c - z*b)*sint;
		yaw.at(1) = y*term_c2 + b*cost + (z*a - x*c)*sint;
		yaw.at(2) = z*term_c2 + c*cost + (x*b - y*a)*sint;
	}
	// Write in vectors to projectile
	p->set_r(rol);
	p->set_p(pit);
	p->set_y(yaw);
}

// Arguments are timestep (for 300 Hz, set t to 1/300) and projectile to be integrated
void PhysicsEngine::verlet_step(float t, Projectile *p) {
	// Read in vectors from projectile
	vector<float> vel = p->get_v();
	vector<float> pos = p->get_d();
	// Get orientiation of source acceleration
	vector<float> acc1 = p->get_r();
	// Initialize output vectors
	vector<float> pos_next = {0,0,0};
	vector<float> vel_next = {0,0,0};
	// Get acceleration magnitude for cycle
	float a = p->get_a();
	// Get rate of angular change
	float r_angle = p->get_r_dot();
	float p_angle = p->get_p_dot();
	// Apply rotations for time step to p
	this->apply_rotation(r_angle*t, 0, p);
	this->apply_rotation(p_angle*t, 1, p);
	// Get orientation of incremented acceleration
	vector<float> acc2 = p->get_r();
	// Iterate over dimensions
	for (int i = 0; i < 3; i++) {
		acc1.at(i) = acc1.at(i) * a;
		acc2.at(i) = acc2.at(i) * a;
		// Perform Verlet
		pos_next.at(i) = pos.at(i) + vel.at(i)*t + 0.5*acc1.at(i)*t*t;
		vel_next.at(i) = vel.at(i) + 0.5*t*(acc1.at(i) + acc2.at(i));
	}
	// Write in vectors to projectile
	p->set_d(pos_next);
	p->set_v(vel_next);
}

void PhysicsEngine::ignite() {}
void PhysicsEngine::cycle() {}
void PhysicsEngine::shutdown() {}
