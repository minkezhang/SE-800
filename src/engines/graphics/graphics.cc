#include "graphics.h"
#include "../physics/projectile.h"
#include "../common/engine.h"
#include "../../classes/control.h"
#include "../../classes/event.h"
#include "../../networks/client.h"

#include <iostream>
#include <osg/Node>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Geode>
#include <osg/Object>
#include <osg/Quat>
#include <osg/StateAttribute>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osg/Vec3>
#include <osg/ShapeDrawable> 
#include <osgDB/ReadFile>
#include <osgViewer/ViewerBase>
#include <ctime>
#include <math.h>

GraphicsEngine::GraphicsEngine() {}

void GraphicsEngine::ignite() {
	// TODO: MOVE CAMERA INIT SOMEWHERE ELSE
	this->prev_roll = osg::Vec3( -99, -99, -99);
	this->prev_pitch = osg::Vec3( -99, -99, -99);
	this->prev_yaw = osg::Vec3( -99, -99, -99);

	this->ship_mesh = "../Assets/ship.obj";
	this->asteroid_mesh = "../Assets/asteroid.obj";

	root = new osg::Group();
	render_world();
	ship_init();
	viewer_init();
}

void GraphicsEngine::cycle() {

	if (this->viewer.done())
		shutdown();

	//clock_t time1 = clock();
	// check packet queue for updates
	// if found object and event packet, compare each object to list of rendered objects
	// for each object which is already rendered, set UpdateObjectCallback (simply a boolean) to true -- this boolean can be mapped to the object
	// for each object we need to render which is not already present, call a function which creates a new object and adds it to the group, sets its updatecallback, etc
	// for each object which was rendered but isn't anymore, remove this object from the group node and free its update callback and free the node
	// SO for each object we need a struct which encompasses the obj ID, the UpdateObjectCallback bool, the object Node, and perhaps the transform matrix?

	send_update_req();
	update_rendered_objects();
	update_camera();
	render();
	reset_rendered_objects();

	//clock_t time2 = clock();
	//clock_t timediff = time2 - time1;
	//float timediff_sec = ((float)timediff) / CLOCKS_PER_SEC;
	//std::cout << "CYCLE LENGTH: " << timediff_sec << "SECONDS" << std::endl;
}

void GraphicsEngine::shutdown() {
	exit(1);
}

osg::Node* GraphicsEngine::create_world_cube() {
	osg::Group* world_cube_root = new osg::Group();

	// Define height, width, and depth values of world cube.
	osg::Box* unit_cube = new osg::Box(osg::Vec3(0, 0, 0), 30000.0f);
	osg::ShapeDrawable* unit_cube_drawable = new osg::ShapeDrawable(unit_cube);
	osg::Geode* basic_shapes_geode = new osg::Geode();

	// Include space texture
	osg::Texture2D* space_face_texture = new osg::Texture2D;
	// Protect texture from being optimized away as a static state.
	space_face_texture->setDataVariance(osg::Object::DYNAMIC);
	osg::Image* space_face = osgDB::readImageFile("../Assets/space.jpg");
	if (!space_face) {
		std::cout << "Couldn't find texture space.jpg" << std::endl;
	}
	space_face_texture->setImage(space_face);

	osg::StateSet* state_set = new osg::StateSet();
	// Assign texture unit 0 of the state set to the texture we just
	// created and enable the texture
	state_set->setTextureAttributeAndModes(
		0, space_face_texture, osg::StateAttribute::ON);
	basic_shapes_geode->setStateSet(state_set);
	basic_shapes_geode->addDrawable(unit_cube_drawable);
	world_cube_root->addChild(basic_shapes_geode);

	return world_cube_root;
}

void GraphicsEngine::render_world() {
	osg::Node* world_cube = create_world_cube();
	osg::PositionAttitudeTransform* world_transform =
		new osg::PositionAttitudeTransform();
	world_transform->addChild(world_cube);
	world_transform->setPosition(osg::Vec3(0, 13, 10));

	this->root->addChild(world_transform);
}

void GraphicsEngine::ship_init() {
	protos::RenderedObj *ship;

	// Wait for ship init packet to be received.
	while (1) {
		this->que_lock.lock();
		if (this->ship_que.size() > 0) {
			ship = this->ship_que.front();
			this->ship_que.pop();
			this->que_lock.unlock();
			break;
		}
		this->que_lock.unlock();
	}

	GraphicsEngine::rendered_obj * ren_obj = create_object(*ship);
	this->main_ship = ren_obj;
}

void GraphicsEngine::viewer_init() {
	// Set up UI update callback
	ClientControl::UIEventHandler* ui_handler = new ClientControl::UIEventHandler(this->net_utils);
	this->viewer.addEventHandler(ui_handler);

	// Assign the scene we created to the viewer
	this->viewer.setSceneData(this->root);
	// Create the windows and start the required threads
	this->viewer.realize();
}

void GraphicsEngine::send_update_req() {
	// Send request to server for objs and events packet.
	int req = 1;
	NetPacket packet;
	PacketUtils::make_packet(&packet, PacketType::OBJS_AND_EVENTS_REQ, (void *) &req, NULL);
	if (!this->net_utils->send_to_server(&packet))
		std::cout << "Could not send objs and events req packet." << std::endl;
}

void GraphicsEngine::update_camera() {
	osg::Matrixd camera_matrix;
	osg::Matrixd camera_rotation;
	osg::Matrixd camera_trans;

	protos::vector roll_vector = this->main_ship->obj.roll_vector();
	protos::vector pitch_vector = this->main_ship->obj.pitch_vector();
	protos::vector yaw_vector = this->main_ship->obj.yaw();

	float r_angle = 0, p_angle = 0, y_angle = 0;

	osg::Vec3 r_vec(roll_vector.x(), roll_vector.y(), roll_vector.z());
	osg::Vec3 p_vec(pitch_vector.x(), pitch_vector.y(), pitch_vector.z());
	osg::Vec3 y_vec(yaw_vector.x(), yaw_vector.y(), yaw_vector.z());

	// Set prev roll, pitch, and yaw if first cycle
/*
	if (this->prev_roll.x() == -99) {
		this->prev_roll = r_vec;
	} else {
		float r_xdot = prev_roll.x()*r_vec.x();
		float r_ydot = prev_roll.y()*r_vec.y();
		float r_zdot = prev_roll.z()*r_vec.z();
		r_angle = acos(r_xdot + r_ydot + r_zdot);
	}

	if (this->prev_pitch.x() == -99) {
		this->prev_pitch = p_vec;
	} else {
		float p_xdot = prev_pitch.x()*p_vec.x();		
		float p_ydot = prev_pitch.y()*p_vec.y();
		float p_zdot = prev_pitch.z()*p_vec.z();
		p_angle = acos(p_xdot + p_ydot + p_zdot);
	}
	
	if (this->prev_yaw.x() == -99) {
		this->prev_yaw = y_vec;
	} else {
		float y_xdot = prev_yaw.x()*y_vec.x();		
		float y_ydot = prev_yaw.y()*y_vec.y();
		float y_zdot = prev_yaw.z()*y_vec.z();
		y_angle = acos(y_xdot + y_ydot + y_zdot);
	}
	// TODO: Update camera based on ship tilts.

	std::cout << "THIS IS ROLL ANGLE :" << r_angle << " THIS IS PITCH ANGLE " << p_angle << " THIS IS YAW ANGLE : " << y_angle << std::endl;
	camera_rotation.makeRotate(
		osg::DegreesToRadians(r_angle), prev_roll,	// roll
		osg::DegreesToRadians(p_angle), prev_pitch,	// pitch
		osg::DegreesToRadians(y_angle), prev_yaw);	// heading
*/

	camera_rotation.makeRotate(
		osg::DegreesToRadians(0.0), osg::Vec3(0, 1, 0),	// roll
		osg::DegreesToRadians(0.0), osg::Vec3(1, 0, 0),	// pitch
		osg::DegreesToRadians(0.0), osg::Vec3(0, 0, 1));	// heading

	prev_roll = r_vec;
	prev_pitch = p_vec;
	prev_yaw = y_vec;	

	// Z axis refers to Y axis, Y axis refers to Z axis
	//std::cout << "THIS IS MAIN SHIP POS: " << this->main_ship->obj.pos().x() << " " << this->main_ship->obj.pos().y() << " " << this->main_ship->obj.pos().z() << "THIS IS ROLL VECTOR " << r_vec.x() << " " << r_vec.y() << " " << r_vec.z() << std::endl;
	//std::cout << "THIS IS YAW VECTOR " << y_vec.x() << " " << y_vec.y() << " " << y_vec.z() << std::endl;

/*
	camera_trans.makeTranslate(this->main_ship->obj.pos().x() - r_vec.x(), this->main_ship->obj.pos().y() - (40*r_vec.y()), this->main_ship->obj.pos().z() + 8 - (10*r_vec.z()));
*/


	camera_trans.makeTranslate(this->main_ship->obj.pos().x(), this->main_ship->obj.pos().y() - 39, this->main_ship->obj.pos().z() + 8);

	camera_matrix = camera_rotation * camera_trans;
	osg::Matrixd inverse = camera_matrix.inverse(camera_matrix);
	this->viewer.getCamera()->setViewMatrix((
		camera_matrix.inverse(camera_matrix) * osg::Matrixd::rotate(-M_PI/2.0, 1, 0, 0)));
}

void GraphicsEngine::render() {
	if (!this->viewer.done()) {
		// Dispatch the new frame, this wraps the following viewer operations:
		// 	advance() to the new frame
		//	eventTraversal() that collects events and passes them on to the 
		// event handlers and event callbacks
		// 	updateTraversal() to call the update callbacks
		//	renderingTraversals() that synchornizes all the rendering threads
		// (if any) and dispatch cull, draw, and swap buffers

		this->viewer.frame();
	}
}

void GraphicsEngine::set_light_source() {
}

void GraphicsEngine::set_shader() {
}

GraphicsEngine::rendered_obj* GraphicsEngine::create_object(protos::RenderedObj obj) {
	osg::Node *node;
	osg::PositionAttitudeTransform* obj_transform =
		new osg::PositionAttitudeTransform();
	if (obj.type() == ObjType::SHIP) {
		node = osgDB::readNodeFile(this->ship_mesh);
		obj_transform->addChild(node);
	} else if (obj.type() == ObjType::ASTEROID) {
		node = osgDB::readNodeFile(this->asteroid_mesh);
		obj_transform->addChild(node);
	}


	// Set position.
	protos::vector pos_vector = obj.pos();
	std::cout << pos_vector.x() << pos_vector.y() << pos_vector.z() << std::endl;
	osg::Vec3 obj_pos(pos_vector.x(), pos_vector.y(), pos_vector.z());
	obj_transform->setPosition(obj_pos);

	float orig_mesh_radius = obj_transform->getBound().radius();
	float desired_radius = obj.size();
	float scale_amt = 1 / (orig_mesh_radius / desired_radius);
	obj_transform->setScale(osg::Vec3(scale_amt, scale_amt, scale_amt));

	if (obj.type() == ObjType::SHIP) {
		obj_transform->setAttitude((osg::Quat(osg::DegreesToRadians(-90.0f),
			osg::Vec3d(0, 0, 1)))*(osg::Quat(osg::DegreesToRadians(20.0f + obj.pitch()*57.295779),
			osg::Vec3d(1, 0, 0)))*(osg::Quat(osg::DegreesToRadians(obj.roll()*57.295779),
			osg::Vec3d(0, 1, 0))));
//		obj_transform->setScale(osg::Vec3(2.0, 2.0, 2.0));
	} else if (obj.type() == ObjType::ASTEROID) {
//		obj_transform->setScale(osg::Vec3(0.2,0.2,0.2));
	}

	std::cout << "THIS IS BOUNDING SPHERE RADIUS " << obj_transform->getBound().radius() << std::endl;

	// Add object to rendered object list.
	rendered_obj *ren_obj = new rendered_obj;
	ren_obj->obj = obj;
	ren_obj->update_pos = false;
  ren_obj->should_render = true;
	ren_obj->trans_matrix = obj_transform;
	cur_objs.insert(std::pair<int, rendered_obj*>(obj.id(), ren_obj));

	this->root->addChild(obj_transform);
	return ren_obj;
}

void GraphicsEngine::remove_object(rendered_obj *ren_obj) {
	root->removeChild(ren_obj->trans_matrix);
	free(ren_obj);
}

void GraphicsEngine::update_object_transform(rendered_obj *ren_obj, protos::RenderedObj update_obj) {
	ren_obj->obj = update_obj;
	ren_obj->update_pos = true;
  ren_obj->should_render = true;

	protos::vector pos_vector = update_obj.pos();
	osg::Vec3 obj_pos(pos_vector.x(), pos_vector.y(), pos_vector.z());
	ren_obj->trans_matrix->setPosition(obj_pos);

	ren_obj->trans_matrix->setAttitude((osg::Quat(osg::DegreesToRadians(-90.0f),
		osg::Vec3d(0, 0, 1)))*(osg::Quat(osg::DegreesToRadians(20.0f + ren_obj->obj.pitch()*57.295779),
		osg::Vec3d(1, 0, 0)))*(osg::Quat(osg::DegreesToRadians(ren_obj->obj.roll()*57.295779),
		osg::Vec3d(0, 1, 0))));
}

void GraphicsEngine::reset_rendered_objects() {
	for (std::map<int, rendered_obj *>::iterator i = cur_objs.begin(); i != cur_objs.end(); ++i) {
		(*i).second->should_render = false;
	}
}

void GraphicsEngine::update_rendered_objects() {
	// TODO: Scan for graphical events and update nodes.

	// Find new objects and events packet
	protos::ObjsAndEventsPacket *packet = new protos::ObjsAndEventsPacket;
	this->que_lock.lock();
	if (this->objs_que.size() > 0) {
		packet = this->objs_que.front();
		this->objs_que.pop();
	} else {
		this->que_lock.unlock();
		return;
	}
	this->que_lock.unlock();
	// Iterate through all rendered object entries in packet
	int updated = 0;
	for (int i = 0; i < packet->obj_size(); ++i) {
		protos::RenderedObj obj = packet->obj(i);
		if (cur_objs.count(obj.id())!= 0) {
			updated++;
			// Case when object has already been rendered in prev cycle.
			rendered_obj* ren_obj = cur_objs.at(obj.id());
			update_object_transform(ren_obj, obj);
		} else {
			// Case when object is being rendered for the first time.
			create_object(obj);
		}
	}

	// Process destroy events.
	for (int i = 0; i < packet->event_size(); ++i) {
		protos::Event event = packet->event(i);
		if (event.event_type() == EventType::DESTROY) {
			std::cout << "RECEIVED REQUEST TO DESTROY OBJECT OF ID " << event.id() << std::endl;
		}
	}

	// Do not render any object which was not sent in update packet.
	if (packet->obj_size() > 0) {
		for (std::map<int, rendered_obj *>::iterator i = cur_objs.begin(); i != cur_objs.end(); ) {
			if ((*i).second->should_render == false) {
				rendered_obj* not_rendered_obj = (*i).second;
				i = cur_objs.erase(i);
				remove_object(not_rendered_obj);
			} else {
				++i;
			}
		}
	}

//	std::cout << "RENDERING " << updated << " OBJECTS" << std::endl;
}
