#include <algorithm>
#include <cstddef>
#include <iostream>

#include "physics.h"

using namespace std;

// public
PhysicsEngine::PhysicsEngine() {
	this->environment = NULL;
}

Environment *PhysicsEngine::get_environment() { return(this->environment); }
void PhysicsEngine::set_environment(Environment *e) { this->environment = e; }

void PhysicsEngine::toggle_a(int id, int val) {
	Projectile *p = this->environment->get_projectile(id);
	if(p != NULL) {
		p->set_a(val * p->get_preset_a());
	}
}

void PhysicsEngine::toggle_p_dot(int id, float val) {
	Projectile *p = this->environment->get_projectile(id);
	if(p != NULL) {
		p->set_p_dot(val * p->get_preset_p_dot());
	}
}

void PhysicsEngine::toggle_r_dot(int id, float val) {
	Projectile *p = this->environment->get_projectile(id);
	if(p != NULL) {
		p->set_r_dot(val * p->get_preset_r_dot());
	}
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
		float term_c1 = (u * x + v * y + w * z) * (1 - cost);
		pit.at(0) = u * term_c1 + x * cost + (v * z - w * y) * sint;
		pit.at(1) = v * term_c1 + y * cost + (w * x - u * z) * sint;
		pit.at(2) = w * term_c1 + z * cost + (u * y - v * x) * sint;
		// Rotate yaw axis around roll by angle
		float term_c2 = (u * a + v * b + w * c) * (1 - cost);
		yaw.at(0) = u * term_c2 + a * cost + (v * c - w * b) * sint;
		yaw.at(1) = v * term_c2 + b * cost + (w * a - u * c) * sint;
		yaw.at(2) = w * term_c2 + c * cost + (u * b - v * a) * sint;
	} else {
		// Rotate roll axis around pitch axis by angle
		float term_c1 = (x * u + y * v + z * w) * (1 - cost);
		rol.at(0) = x * term_c1 + u * cost + (y * w - z * v) * sint;
		rol.at(1) = y * term_c1 + v * cost + (z * u - x * w) * sint;
		rol.at(2) = z * term_c1 + w * cost + (x * v - y * u) * sint;
		// Rotate yaw axis around pitch axis by angle
		float term_c2 = (x * a + y * b + z * c) * (1 - cost);
		yaw.at(0) = x * term_c2 + a * cost + (y * c - z * b) * sint;
		yaw.at(1) = y * term_c2 + b * cost + (z * a - x * c) * sint;
		yaw.at(2) = z * term_c2 + c * cost + (x * b - y * a) * sint;
	}

	// Write in vectors to projectile
	p->set_r(rol);
	p->set_p(pit);
	p->set_y(yaw);
}

// Verlet 1:
void PhysicsEngine::verlet_step(float t, Projectile*p) {
  Grid *old_g = this->environment->get_grid(p);

  // Read in vectors from projectile
  vector<float> vel = p->get_v();
  vector<float> pos = p->get_d();
  
  // Get scalables
  vector<float> pos_next = {0,0,0};
  vector<float> vel_next = {0,0,0};
  float a = p->get_a();
  
  // Get rate of angular change
  float r_angle = p->get_r_dot();
  float p_angle = p->get_p_dot();

  // Apply rotations for time step to p
  vector<float> roll = p->get_r();
  vector<float> pitch = p->get_p();
  vector<float> yaw = p->get_y();
  this->apply_rotation(r_angle*t, 0, p);
  this->apply_rotation(p_angle*t, 1, p);
  vector<float> new_orient = p->get_r();
  
  // Reorient velocity
  float vx = vel.at(0);
  float vy = vel.at(1);
  float vz = vel.at(2);
  float mag = sqrt(vx*vx + vy*vy + vz*vz);


  // Iterate over
  int i = 0;
  if (mag < p->get_preset_max_vel()) {
 	for (i = 0; i < 3; i++) {
   	 	pos_next.at(i) = pos.at(i) + vel.at(i)*t;
    	vel_next.at(i) = new_orient.at(i) * (mag + a * t);
    }
  } else {
  	for (i = 0; i < 3; i++) {
    	pos_next.at(i) = pos.at(i) + vel.at(i) * t;
    	vel_next.at(i) = new_orient.at(i) * mag;
    }
  }
 
    // resolves bounding problems
  	for (i = 0; i < 3; i++) {
    	if(pos_next.at(i) < 0) {
      		pos_next.at(i) += this->environment->get_size().at(i);
    	} else if(pos_next.at(i) >= this->environment->get_size().at(i)) {
      		pos_next.at(i) -= this->environment->get_size().at(i);
    	}
    }
  
	if (p->get_type() == SHIP) {
		cout << "Ship Position: (x = " << pos_next.at(i) << ", y = " << pos_next.at(i) << ", z = " << pos_next.at(i) << std::endl;
	}

  // Write in vectors to projectile
  p->set_d(pos_next);
  p->set_v(vel_next);

  // update grids
  Grid *new_g = this->environment->get_grid(p);
  old_g->del_projectile(p);
  new_g->add_projectile(p);
}
    
/*
// Verlet 2:
// Arguments are timestep (for 300 Hz, set t to 1/300) and projectile to be integrated
void PhysicsEngine::verlet_step(float t, Projectile *p) {
	Grid *old_g = this->environment->get_grid(p);

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
	this->apply_rotation(r_angle * t, 0, p);
	this->apply_rotation(p_angle * t, 1, p);
	// Get orientation of incremented acceleration
	vector<float> acc2 = p->get_r();
	// Iterate over dimensions
	for (int i = 0; i < 3; i++) {
		acc1.at(i) = acc1.at(i) * a;
		acc2.at(i) = acc2.at(i) * a;
		// Perform Verlet
		pos_next.at(i) = pos.at(i) + vel.at(i) * t + 0.5 * acc1.at(i) * t * t;
		vel_next.at(i) = vel.at(i) + 0.5 * t * (acc1.at(i) + acc2.at(i));

		// resolves bounding problems
		if(pos_next.at(i) < 0) {
			pos_next.at(i) += this->environment->get_size().at(i);
		} else if(pos_next.at(i) >= this->environment->get_size().at(i)) {
			pos_next.at(i) -= this->environment->get_size().at(i);
		}
	}
	// Write in vectors to projectile
	p->set_d(pos_next);
	p->set_v(vel_next);

	// update grids
	Grid *new_g = this->environment->get_grid(p);
	old_g->del_projectile(p);
	new_g->add_projectile(p);
}
*/

void PhysicsEngine::collision_check(Projectile *p) {
	std::vector<Projectile *> neighbors = this->environment->get_neighbors(p);
	for(std::vector<Projectile *>::iterator i = neighbors.begin(); i != neighbors.end(); ++i) {
		Projectile *q = *i;
		if(p->get_id() != q->get_id()) {
			if(!q->get_is_destroyed()) {
				std::vector<float> p_d = p->get_d();
				std::vector<float> q_d = q->get_d();
				std::vector<float> diff;
				// get the distance between the projectiles
				//	cf. http://bit.ly/1sPHU1c
				std::transform(p_d.begin(), p_d.end(), q_d.begin(), std::back_inserter(diff), [](float a, float b) { return(a - b); });
				float dist_sq = 0;
				for(int i = 0; i < 3; i++) {
					dist_sq += diff.at(i) * diff.at(i);
				}
				int collide = dist_sq < (p->get_size() + q->get_size()) * (p->get_size() + q->get_size());
				if(collide) {
					this->collide(p, q);
				}
			}
		}
	}
}

/**
 * primitive damage modeling
 */
void PhysicsEngine::collide(Projectile *p, Projectile *q) {
	if(q->get_is_clippable()) {
		// bullets are destroyed
		p->damage(q->get_cur_tolerance());
		q->damage(q->get_cur_tolerance());
	} else {
		// clippable objects are checked twice (unfortunately) -- this prevents double counting the damage
		/**
		 * TODO -- may want to scale up with velocity of the objects in question
		 *	does not need to be strictly linear scale -- can just use v_squared
		 */
		p->damage(q->get_cur_tolerance() * 0.5);
		q->damage(p->get_cur_tolerance() * 0.5);
	}
}

void PhysicsEngine::ignite() {}
void PhysicsEngine::cycle() {
	std::vector<Projectile *> clippable = this->environment->get_clippable();
	std::vector<Projectile *> unclippable = this->environment->get_unclippable();

	/**
	 * calling del_projectile in such a way should be okay in this instance
	 *	the main concern would be modifying a list while iterating, which we are NOT doing (as
	 *	clippable[] and unclippable[] here are copies)
	 * calls to get_neighbor() later are not cached, and thus will have an updated copy of neighbors,
	 *	with all projectiles that were deleted here cut out
	 */
	for(std::vector<Projectile *>::iterator i = unclippable.begin(); i != unclippable.end(); ++i) {
		Projectile *p = *i;
		if(p->get_is_destroyed()) {
			this->environment->del_projectile(p);
		} else {
			this->verlet_step(.0033, p);
			p->set_lifetime();
		}
	}
	for(std::vector<Projectile *>::iterator i = clippable.begin(); i != clippable.end(); ++i) {
		Projectile *p = *i;
		if(p->get_is_destroyed()) {
			if(p->get_is_processed()) {
				this->environment->del_projectile(p);
			}
		} else {
			this->verlet_step(.0033, p);
			// only clippable objects need to be checked for collisions against other objects
			this->collision_check(p);
			p->set_lifetime();
		}
	}
}
void PhysicsEngine::shutdown() {}
