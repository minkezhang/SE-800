#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <map>
#include <mutex>
#include <osg/Group>
#include <osg/Node>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osgViewer/Viewer>
#include <vector>
#include <queue>

#include "../physics/projectile.h"
#include "../common/engine.h"
#include "../../classes/control.h"
#include "../../classes/gameaudio.h"
#include "../../classes/ship.h"
#include "../../networks/client.h"
#include "../../networks/packetprotos.pb.h"

class GraphicsEngine : public Engine {
	struct rendered_obj {
		float obj_roll;
		float obj_pitch;
		float obj_size;
		osg::Vec3 obj_pos;
		osg::Vec3 obj_roll_vector;
		osg::Vec3 obj_pitch_vector;
		osg::Vec3 obj_yaw_vector;
    bool should_render;
		osg::PositionAttitudeTransform* trans_matrix;
	};

	public:
		GraphicsEngine(string color);

		queue<protos::ObjsAndEventsPacket *> objs_que;
		queue<protos::RenderedObj *> ship_que;
		std::mutex que_lock;
		ClientNetUtils *net_utils;

		void ignite();
		void cycle();
		void shutdown();

	private:
		int team_id;
		osg::Group *root;
		ClientControl::UIEventHandler* ui_handler;
		GameAudio *audio;
		osg::Vec4 player_color;
		rendered_obj *main_ship;
		osgViewer::Viewer viewer;
		string ship_mesh;
		string asteroid_mesh;
		string bullet_mesh;
		osg::Vec3 prev_roll;
		osg::Vec3 prev_pitch;
		osg::Vec3 prev_yaw;

		std::map<int, rendered_obj*> cur_objs;

		std::vector<float> size;				// size of world
		osg::Node* create_world_cube();
		void render_world();						// draw world cube from pre-loaded dimensions and assets
		void ship_init();								// creates the user-controlled ship
		void viewer_init();							// initializes callbacks, viewing window, and scene
		void audio_init();							// Initializes game audio
		void send_update_req();					// sends req for objs and events from server
		void update_camera();						// positions the camera behind used-controlled ship
		void reset_rendered_objects();	// sets all rendered objects for removal (these objects will be removed in next cycle if not requested to be rendered again)
		void update_rendered_objects();	// updates object positions and triggers graphical events
		void render();									// renders the world graph
		rendered_obj* create_object(protos::RenderedObj obj);		// creates a new object to be rendered
		void remove_object(rendered_obj *ren_obj);
		void update_object_transform(rendered_obj *ren_obj, protos::RenderedObj update_obj);		// updates pos and tilt of obj rendered in last cycle

		void set_light_source();
		void set_shader();

};

#endif
