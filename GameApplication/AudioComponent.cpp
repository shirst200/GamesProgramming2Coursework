/*
=================
AudioComponent.cpp
- CPP file for class definition - IMPLEMENTATION
- CPP file for the AudioComponent class
=================
*/
#include "AudioComponent.h"
#include "SDKwavefile.h"

/*
=================
- Data constructor initializes the AudioComponent object 
- Is always called, thus ensures all AudioComponent objects are in a consistent state.
=================
*/
AudioComponent::AudioComponent()
{
	//Audio is playing at start
	pausedMusic = false;
	HRESULT hResult;
	// Initialize XAudio2
	CoInitializeEx( NULL, COINIT_MULTITHREADED );
	
	// create an XAudio2 instance
    if( FAILED( hResult = XAudio2Create( &mXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR  ) ) )
    {
        CoUninitialize();
    }
	else
    if( FAILED( hResult = mXAudio2->CreateMasteringVoice( &mMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL  ) ) )
    {
        mXAudio2->Release();
        CoUninitialize();
    }

}
/*
=================
- Destructor, cleans up after the cXAudio object is deleted
=================
*/
AudioComponent::~AudioComponent()
{
	// Destroy the source voice instance
	mSourceVoice->DestroyVoice();
	// Destroy the voice instance
	mMasteringVoice->DestroyVoice();

	// Release the XAudio2 instance
	mXAudio2->Release();
    CoUninitialize();
}

/*
=================
- Play sound.
=================
*/
void AudioComponent::playSound(LPWSTR theFilename, bool pLoop )					// Play sound
{
	HRESULT hResult;
	CWaveFile wavFile;

	wavFile.Open( theFilename, NULL, WAVEFILE_READ );
    // Get format of wave file
    WAVEFORMATEX* pwfx = wavFile.GetFormat();

    // Calculate how many bytes and samples are in the wave
    DWORD cbWaveSize = wavFile.GetSize();

    // Read the sample data into memory
    BYTE* pbWaveData = new BYTE[ cbWaveSize ];

    wavFile.Read( pbWaveData, cbWaveSize, &cbWaveSize );

    // Submit the wave sample data using an XAUDIO2_BUFFER structure
    XAUDIO2_BUFFER buffer = {0};
    buffer.pAudioData = pbWaveData;
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = cbWaveSize;
	if (pLoop)
	{
		buffer.LoopLength = 0;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

    // Create the source voice
    if( FAILED( hResult = mXAudio2->CreateSourceVoice( &mSourceVoice, pwfx ) ) )
    {
        delete pbWaveData;
    }
	else
	{
		mSourceVoice->SubmitSourceBuffer(&buffer);
		mSourceVoice->Start(0, XAUDIO2_COMMIT_NOW );
	}


}

void AudioComponent::pauseSound()
{
    if (!pausedMusic)
    {
        mXAudio2->StopEngine();
		pausedMusic=true;
    }
	else{
		pausedMusic=false;
		mXAudio2->StartEngine();
	}
}