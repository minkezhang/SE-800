#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <list>

//  std::map used to search for object IDs in constant time.
#include <map>

#include "../common/engine.h"
#include "../../classes/ship.h"

class GraphicsEngine : public Engine {
	public:
		GraphicsEngine();
		~GraphicsEngine();

		/**
		 * consider allowing the NetworkEngine to fill the current object list -- the graphics engine would therefore only need to check
		 *	cur_objects is not empty and render on-demand
		 *
		 * challenges to consider -- sync NetworkEngine with GraphicsEngine cycle frequency (60Hz), unreliability of network, etc.
		 */
		void fill_cur_objects(Projectile *projectiles);

		/**
		 * Will there be no front-facing function calls?
		 */

	private:
		int team_id;

		std::map<int, Ship> old_ships;			// all ships, including current ship
		std::map<int, Asteroid> old_asteroids;

		std::map<int, Ship> cur_ships;
		std::map<int, Asteroid> cur_asteroids;

		std::vector<float> size;			// size of world
		void render_world();				// draw world cube from pre-loaded dimensions and assets
		void render_camera();				// position the camera behind rendered ship -- interpolate camera position based on timestep delta

		void render_objects();				// draw and interpolate position of each object kept in memory

		void set_light_source();
		void set_shader();

		/**
		 * see public function for alternative strategy
		 * void fill_cur_objects();			// gets new objects -- an incoming network packet handler
		 */
		void fill_old_objects();			// copies cur_objects into old_objects at the end of the cycle
};

#endif
