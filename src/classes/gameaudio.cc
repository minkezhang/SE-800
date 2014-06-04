#include "gameaudio.h"
#include "../engines/graphics/graphics.h"
#include "../engines/physics/projectile.h"

#include <osgAudio/FileStream.h>
#include <osgAudio/SoundManager.h>
#include <osgAudio/SoundRoot.h>
#include <osgAudio/SoundState.h>
#include <osg/DeleteHandler>
#include <osg/Group>
#include <osgDB/FileUtils>
#include <osgViewer/Viewer>

GameAudio::GameAudio(osg::Group *root, osgViewer::Viewer *viewer) : root(root), viewer(viewer) {
}

void GameAudio::init() {
	osgAudio::SoundManager::instance()->init( 16, true );
	osgAudio::SoundManager::instance()->getEnvironment()->setDistanceModel(osgAudio::InverseDistance);
	osgAudio::SoundManager::instance()->getEnvironment()->setDopplerFactor(1);

	explosion_audio_init();
	munition_audio_init();
	background_audio_init();

	this->sound_root = new osgAudio::SoundRoot;
	this->sound_root->setCamera(this->viewer->getCamera());
	this->root->addChild(sound_root.get());
}

void GameAudio::shutdown() {
	if (osg::Referenced::getDeleteHandler()) {
			osg::Referenced::getDeleteHandler()->setNumFramesToRetainObjects(0);
			osg::Referenced::getDeleteHandler()->flushAll();
	}
	osgAudio::SoundManager::instance()->shutdown();
}

void GameAudio::explosion_audio(osg::Vec3 ren_obj_pos) {
	osgAudio::SoundState *explosion_sound_state = osgAudio::SoundManager::instance()->findSoundState("explosion");
	explosion_sound_state->setPosition(ren_obj_pos);
	explosion_sound_state->setPlay(true);
	int priority = 10;
	osgAudio::SoundManager::instance()->pushSoundEvent(explosion_sound_state, priority);
}

void GameAudio::munition_audio(int munition_type) {
	osgAudio::SoundState *munition_sound_state;
	if (munition_type == ObjType::BULLET) {
		munition_sound_state = osgAudio::SoundManager::instance()->findSoundState("bullet");
	} else if (munition_type == ObjType::BOMB) {
		munition_sound_state = osgAudio::SoundManager::instance()->findSoundState("bomb");
	}
	//TODO: Add missile audio
	// Only play munition audio of main player
	float x, y, z;
	osgAudio::SoundManager::instance()->getListener()->getPosition(x, y, z);
	munition_sound_state->setPosition(osg::Vec3(x, y, z));
	munition_sound_state->setPlay(true);
	int priority = 10;
	osgAudio::SoundManager::instance()->pushSoundEvent(munition_sound_state, priority);
}

void GameAudio::background_audio_init() {
	osg::ref_ptr<osgAudio::SoundState> musicSoundState = osgAudio::SoundManager::instance()->findSoundState("music");
	if (!musicSoundState) {
		// If not found, create a new sound state
		musicSoundState = new osgAudio::SoundState("music");
		// Allocate a hw source so we can loop it
		musicSoundState->allocateSource(10);
		// Create a new filestream that streams samples from a ogg-file.
		osgAudio::FileStream *musicStream = new osgAudio::FileStream("../Assets/backgroundmusic.ogg");
		// Associate the stream with the sound state
		musicSoundState->setStream(musicStream);
		// Make it an ambient (heard everywhere) sound
		musicSoundState->setAmbient(true);
		// Loop the sound forever
		musicSoundState->setLooping(true);
		// Start playing the music!
		musicSoundState->setPlay(true);
		// Add the soundstate to the sound manager so we can find it later on.
		osgAudio::SoundManager::instance()->addSoundState(musicSoundState.get());
	}
}

void GameAudio::explosion_audio_init() {
	osgAudio::Sample *sample = new osgAudio::Sample(
		osgDB::findDataFile("../Assets/explosion.wav"));
	osg::ref_ptr<osgAudio::SoundState> sound_state = new osgAudio::SoundState("explosion");
	sound_state->setSample(sample);
	sound_state->setGain(0.7f);
	sound_state->setPitch(1);
	sound_state->setReferenceDistance(10);
	sound_state->setPlay(false);
	sound_state->setLooping(false);

	osgAudio::SoundManager::instance()->addSoundState(sound_state.get());
}

void GameAudio::munition_audio_init() {
	osgAudio::Sample *bullet_sample = new osgAudio::Sample(
		osgDB::findDataFile("../Assets/bullet/bullet1.wav"));
	osg::ref_ptr<osgAudio::SoundState> bullet_sound_state = new osgAudio::SoundState("bullet");
	bullet_sound_state->setSample(bullet_sample);
	bullet_sound_state->setGain(0.7f);
	bullet_sound_state->setReferenceDistance(10);
	bullet_sound_state->setPlay(false);
	bullet_sound_state->setLooping(false);
	osgAudio::SoundManager::instance()->addSoundState(bullet_sound_state.get());


	osgAudio::Sample *bomb_sample = new osgAudio::Sample(
		osgDB::findDataFile("../Assets/bomb.wav"));
	osg::ref_ptr<osgAudio::SoundState> bomb_sound_state = new osgAudio::SoundState("bomb");
	bomb_sound_state->setSample(bomb_sample);
	bomb_sound_state->setGain(0.7f);
	bomb_sound_state->setReferenceDistance(10);
	bomb_sound_state->setPlay(false);
	bomb_sound_state->setLooping(false);
	osgAudio::SoundManager::instance()->addSoundState(bomb_sound_state.get());

	// TODO: Add missile sound state.

}

