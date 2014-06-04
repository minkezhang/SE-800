#include "projectile.h"

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

Projectile::Projectile(
	int id, int is_clippable, float mass, float max_tolerance,
	vector<float> d, vector<float> v,
	float size,
	vector<float> p, vector<float> r, vector<float> y,
	float p_dot, float r_dot,
	float preset_a, float preset_p_dot, float preset_r_dot, int lifetime
	) : id(id), is_clippable(is_clippable), mass(mass), max_tolerance(max_tolerance),
		d(d), v(v),
		size(size),
		p(p), r(r), y(y),
		p_dot(p_dot), r_dot(r_dot),
		preset_a(preset_a), preset_p_dot(preset_p_dot), preset_r_dot(preset_r_dot), preset_max_vel(1500), lifetime(lifetime) {
}

// GET FUNCTIONS

int Projectile::get_id() { return this->id; }
float Projectile::get_size() { return this->size; }
int Projectile::get_mass() { return this->mass; }
int Projectile::get_type() { return this->type; }
float Projectile::get_cur_tolerance() { return this->cur_tolerance; }
float Projectile::get_max_tolerance() { return this->max_tolerance; }

int Projectile::get_is_destroyed() { return this->is_destroyed; }
int Projectile::get_is_processed() { return this->is_processed; }
int Projectile::get_is_clippable() { return this->is_clippable; }

vector<float> Projectile::get_d() { return this->d; }
vector<float> Projectile::get_v() { return this->v; }
float Projectile::get_a() { return this->a; }

vector<float> Projectile::get_p() { return this->p; }
vector<float> Projectile::get_y() { return this->y; }
vector<float> Projectile::get_r() { return this->r; }
float Projectile::get_p_dot() { return this->p_dot; }
float Projectile::get_r_dot() { return this->r_dot; }

float Projectile::get_preset_a() { return(this->preset_a); }
float Projectile::get_preset_p_dot() { return(this->preset_p_dot); }
float Projectile::get_preset_r_dot() { return(this->preset_r_dot); }
float Projectile::get_preset_max_vel() { return(this->preset_max_vel); }
int Projectile::get_lifetime() { return(this->lifetime); }

// SET FUNCTIONS

void Projectile::set_d(vector<float> d) { this->d = d; }
void Projectile::set_a(float a) { this->a = a; }
void Projectile::set_v(vector<float> v) { 
  float max_v = this->preset_max_vel;
  float vx = v.at(0);
  float vy = v.at(1);
  float vz = v.at(2);
  float curr_mag = sqrt(vx * vx + vy * vy + vz * vz);
  if (curr_mag < max_v) {
    this->v = v;
  } else {
    vector<float> vmod = {0,0,0};
    vmod.at(0) = vx * max_v / curr_mag;
    vmod.at(1) = vy * max_v / curr_mag;
    vmod.at(2) = vz * max_v / curr_mag;
    this->v = vmod;
  }  
}


void Projectile::set_p(vector<float> p) { this->p = p; }
void Projectile::set_y(vector<float> y) { this->y = y; }
void Projectile::set_r(vector<float> r) { this->r = r; }
void Projectile::set_p_dot(float p_dot) { this->p_dot = p_dot; }
void Projectile::set_r_dot(float r_dot) { this->r_dot = r_dot; }

void Projectile::set_is_processed() { this->is_processed = 1; }

void Projectile::set_lifetime() {
	if(this->lifetime > 0) {
		this->lifetime--;
	}
	if(this->lifetime == 0) {
		this->is_destroyed = 1;
	}
}

void Projectile::damage(float tolerance) {
	this->cur_tolerance -= tolerance;
	if(this->cur_tolerance <= 0) {
		this->cur_tolerance = 0;
		this->is_destroyed = 1;
	}
}
