#ifndef _GAMEAUDIO_H
#define _GAMEAUDIO_H

#include <osgAudio/SoundManager.h>
#include <osgAudio/SoundRoot.h>
#include <osg/Group>
#include <osg/Node>
#include <osgViewer/Viewer>

class GameAudio {
	public:
		// Only initialize after root and viewer have been initialized.
		GameAudio(osg::Group *root, osgViewer::Viewer *viewer);
		void init();
		void shutdown();
		void explosion_audio(osg::Vec3 ren_obj_pos);
		void munition_audio(int munition_type);
	private:
		osg::ref_ptr<osgAudio::SoundRoot> sound_root;
		osg::Group *root;
		osgViewer::Viewer *viewer;
		void background_audio_init();
		void explosion_audio_init();
		void munition_audio_init();
};

#endif
