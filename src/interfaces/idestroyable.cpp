#include "../interfaces/iobject.cpp"

class IDestroyable : public IObject {
	public:
		virtual int get_is_dead();
		virtual int get_health();

		/* calls set_health to decrement damage */
		virtual void take_damage(int dmg);

	private:
		int is_dead;		// physics engine ignores collisions with all objects marked is_dead
		int health;		// health remaining

		/* set is_dead = 1 if health <= 0 */
		virtual void set_health(int health);
};
