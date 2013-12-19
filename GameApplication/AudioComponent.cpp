//.cpp file for the Audio Component class

#include "AudioComponent.h"		//methods associated with AudioComponent
#include "SDKwavefile.h"		//Cwavefile functionality


AudioComponent::AudioComponent()	//initialises the Audio Component object, is always called
{
	pausedMusic = false;			//audio is playing on start
	HRESULT hResult;
	CoInitializeEx( NULL, COINIT_MULTITHREADED );	//initialise the XAudio2 object
	
    if( FAILED( hResult = XAudio2Create( &mXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR  ) ) )		//create an XAudio2 object instance
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

AudioComponent::~AudioComponent()		//Destructor, called when audio object is deleted
{
	mSourceVoice->DestroyVoice();		//Destroy instance of the source voice
	mMasteringVoice->DestroyVoice();	//Destroy instance of the mastering voice

	mXAudio2->Release();				//Release xAudio2 instance
    CoUninitialize();
}


void AudioComponent::playSound(LPWSTR theFilename, bool pLoop )		//Play sound, takes in audio filename and if it should loop
{
	HRESULT hResult;
	CWaveFile wavFile;		//sound must be a .wav file

	wavFile.Open( theFilename, NULL, WAVEFILE_READ );		//read file
    WAVEFORMATEX* pwfx = wavFile.GetFormat();				//get format of the wav file

    DWORD cbWaveSize = wavFile.GetSize();					//Calculate the wave's samples and bytes

    BYTE* pbWaveData = new BYTE[ cbWaveSize ];				//read sample data into memory

    wavFile.Read( pbWaveData, cbWaveSize, &cbWaveSize );	//read all of the above into memory

    XAUDIO2_BUFFER buffer = {0};			//submit the data using the XAUDIO2_BUFFER struct
    buffer.pAudioData = pbWaveData;			//assign the wave data to the buffer's audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
    buffer.AudioBytes = cbWaveSize;			//assign the wave size to the buffer's audio data
	if (pLoop)								//if the sound should loop
	{
		buffer.LoopLength = 0;						//loop immediately after sound is finished
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;	//loop an infinite number of times
	}

    if( FAILED( hResult = mXAudio2->CreateSourceVoice( &mSourceVoice, pwfx ) ) )	//create source voice
    {
        delete pbWaveData;
    }
	else
	{
		mSourceVoice->SubmitSourceBuffer(&buffer);
		mSourceVoice->Start(0, XAUDIO2_COMMIT_NOW );
	}


}

void AudioComponent::pauseSound()		//pause the music
{
    if (!pausedMusic)					//if the user has pressed F to pause music
    {
        mXAudio2->StopEngine();			//stop the XAudio2 engine from playing the sound
		pausedMusic=true;
    }
	else{
		pausedMusic=false;				//the song is no longer paused; the user has pressed F while already paused
		mXAudio2->StartEngine();		//unpause the music, let the XAudio2 engine play the sound
	}
}