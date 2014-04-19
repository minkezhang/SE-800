



IPhysics

Public:

void set_a(float throttle_input);

void set_tdot(float roll_input);

void set_pdot(float pitch_input);

void add_obj(IObject obj_input);

void del_obj(int ID);



Steven Garcia - Contract for Physics Engine

IObject


Public:

void set_dead(int set);

void set_id(IObject obj_input);

float get_mass();

vec get_velocity();

vec get_pitch();

vec get_roll();

// For asteroids only. For ships, velocity and orientation are the same
vec get_orient();

void set_velocity(vec);

void set_pitch(vec);

void set_roll(vec);

float get_radius();

float get_force_vec();

void set_force_vec(float);

vec get_posn();

void set_posn(vec);
