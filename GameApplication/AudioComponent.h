//define basic functionality for the AudioComponent class

#ifndef _CXAUDIO_H
#define _CXAUDIO_H
#include <xaudio2.h>			//functionality to allow creation of audio objects
#include "GameComponent.h"		//is a type of GameComponent, including all general methods

class AudioComponent:public GameComponent
{
private:
    IXAudio2* mXAudio2;			//objects used to hold sound
    IXAudio2MasteringVoice* mMasteringVoice;
	IXAudio2SourceVoice* mSourceVoice;
	bool pausedMusic;			//whether or not the user pauses the music
		
public:
	AudioComponent();										//default constructor
	~AudioComponent();										//default destructor
	void playSound(LPWSTR theFilename, bool pLoop );		//play sound, taking in the song's file and whether it should loop
	void pauseSound();										//pause sound
};
#endif