#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <list>
#include <map>
#include "../common/iengine.h"

class GraphicsEngine : public IEngine {
        public:
                GraphicsEngine();
                ~GraphicsEngine();

        private:
                int team_id;
                std::list<Grid> map_grids;
                //  std::map used to search for object IDs in constant time.
                std::map<int, AI_ship> old_rendered_ai_ships;
                std::map<int, Asteroid> old_rendered_asteroids;
                player_ship old_rendered_player_ship;
                std::map<int, AI_ship> new_rendered_ai_ships;
                std::map<int, Asteroid> new_rendered_asteroids;
                player_ship new_rendered_player_ship;

                // draw_world: Draws world cube from preloaded dimensions and
                // assets.
                void draw_world();

                // update_camera: Positions the camera behind the newest
                // position of the player ship. If the ship roll and pitch
                // have changed from the last cycle, interpolates the camera
                // view based on the changes of roll and pitch.
                void update_camera(); 

                // draw_objects: Draw and/or interpolate the position of each
                // object found in list of map grids.
                // This means, draw all new_rendered_* objects.
                // If any of these objects are present as old_rendered_* objs,
                // (and have thus been rendered in last cycle), 
                // interpolate object position based on object's new location.
                void draw_objects();

                void set_light_source();

                void set_shader();

                // update_obj_data: Called after get_map_grids. Fills in
                // new_rendered_* objects with updated map grid objects.
                void update_obj_data();

                // set_obj_data_as_old: Called at the end of cycle. Sets
                // all new_rendered_* objects to old_rendered_* objects.
                void set_obj_data_as_old();


                // Functions to interface with Network.

                // get_map_grids: Sends client ID to server and waits for
                // list of map grids to render. Can also be receive the
                // world state upon alt. network configuration.
                void get_map_grids_from_net();
};

#endif
