

/*
=================
AudioComponent.h
- Header file for class definition - SPECIFICATION
- Header file for the AudioComponent class
=================
*/
#ifndef _CXAUDIO_H
#define _CXAUDIO_H
#include <xaudio2.h>
#include "GameComponent.h"

class AudioComponent:public GameComponent
{
private:
    IXAudio2* mXAudio2;
    IXAudio2MasteringVoice* mMasteringVoice;
	IXAudio2SourceVoice* mSourceVoice;
	bool pausedMusic;

public:
	AudioComponent();						// Default constructor
	~AudioComponent();						// Default destructor
	void playSound(LPWSTR theFilename, bool pLoop );		// Play sound
	void pauseSound();
};
#endif