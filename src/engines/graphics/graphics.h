#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

//  std::map used to search for object IDs in constant time.
#include <map>
#include <mutex>
#include <osg/Group>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <vector>
#include <queue>

#include "../physics/projectile.h"
#include "../common/engine.h"
#include "../../classes/ship.h"
#include "../../networks/client.h"
#include "../../networks/packetprotos.pb.h"

class GraphicsEngine : public Engine {
	struct rendered_obj {
		protos::RenderedObj* obj;
		bool update_pos;
		osg::Node* node;
		osg::PositionAttitudeTransform* trans_matrix;
	};

	public:
		GraphicsEngine();

		queue<protos::RenderedObj> packet_que;
		std::mutex que_lock;
		ClientNetUtils *net_utils;

		/**
		 * consider allowing the NetworkEngine to fill the current object list -- the graphics engine would therefore only need to check
		 *	cur_objects is not empty and render on-demand
		 *
		 * challenges to consider -- sync NetworkEngine with GraphicsEngine cycle frequency (60Hz), unreliability of network, etc.
		 */
		void ignite();
		void cycle();
		void shutdown();
		void fill_cur_objects(Projectile *projectiles);

		/**
		 * Will there be no front-facing function calls?
		 */

	private:
		int team_id;
		osg::Group *root;
		protos::RenderedObj main_ship;
		osgViewer::Viewer viewer;

		std::map<int, rendered_obj*> old_ships;			// all ships, including current ship
		//std::map<int, Asteroid> old_asteroids;

		std::map<int, rendered_obj*> cur_ships;
		std::map<int, rendered_obj*> cur_asteroids;

		std::vector<float> size;			// size of world
		osg::Node* create_world_cube();
		void render_world();				// draw world cube from pre-loaded dimensions and assets
		void ship_init();
		void viewer_init();
		void update_camera();				// position the camera behind rendered ship -- interpolate camera position based on timestep delta

		void render_objects();				// draw and interpolate position of each object kept in memory

		void set_light_source();
		void set_shader();

		/**
		 * see public function for alternative strategy
		 * void fill_cur_objects();			// gets new objects -- an incoming network packet handler
		 */
		void update_rendered_objects();			// copies cur_objects into old_objects at the end of the cycle
};

#endif
