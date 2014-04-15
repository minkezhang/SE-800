#include "../interfaces/iobject.cpp"

class IDestroyable : public IObject {
	public:
		virtual int get_is_dead() {
			return(this->is_dead);
		}
		virtual int get_health() {
			return(this->health);
		}
		virtual void take_damage(int dmg) {
			this->set_health(this->health - dmg);
			if(this->health <= 0) {
				this->is_dead = 1;
			}
		}
	private:
		int is_dead;		// physics engine ignores collisions with all objects marked is_dead
		int health;		// health remaining

		virtual void set_health(int health) {
			this->health = health;
		}
};
