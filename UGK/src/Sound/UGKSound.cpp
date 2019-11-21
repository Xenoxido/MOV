/**	Definition of the class Sound for the UPV Game Kernel

*	Prefix: UGKSND_

*	@author Ramon Molla
*	@version 2014-05
*	@Upgrade Carlos Martinez Perez - 2012-05
*	@NewVersion Ramón Mollá 2012-07
*	@NewVersion Alfonso Pérez 2013-03
*	@NewVersion Ramón Mollá 2014-05 - API conversion and refactoring
*/

#include <UGKSound.h>

#ifdef UGKOS_WINDOWS
	#ifndef WINDOWS_LOADED
	#define WINDOWS_LOADED
	#include <windows.h>
	#endif
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

#include <math.h>

#ifdef UGKSND_FMOD375
#elif defined (UGKSND_FMODEx)
#elif defined (UGKSND_OAL)
#elif defined (UGKSND_SDL)
#endif

#define UGKSND_NO_CHANNEL   -1
#define UGKSND_ANY_CHANNEL  -1
#define UGKSND_ALL_CHANNELS -1

using namespace UGK;

/**
*	\fn void CSound::CSound(CString P,int v, CString c)
*	Constructor of the class.
*	\param[in] Name Path where the sound is
*	\param[in] Vol Volume of the sound
*	\param[in] Path Path where the sound is
*/
CSound::CSound(UGKS_String Name, int Vol, UGKS_String Path)
{
	Init(Name, Vol, Path);
}

/**
*	\fn void CSound::~CSound()
*	Destructor of the Class. Close the Stream.
*/
CSound::~CSound(){}

/**
*	\fn void CSound::Load()
*	\brief Load and Store a sample in memory
*/

void CSound::Load()
{
	
}

#ifdef UGKSND_FMOD375 

void CSound::SetVolume2() { SoundCard->SetChannelVolume(Channel, Volume);}

/**
*	\fn void CSound::Play (int v)
*	Plays a given sound
*	\param[in] v Volume to play this sound (also modify the parameter of the object)
*/
void CSound::Play (int v)
{
	
}

#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
	// These functions use the "sourceID" added as a class atribute

	// Plays a sound at 
	void CSound::Play(int vol){

	}

	void CSound::Play(){

	}

	void CSound::SetVolume2()
	{

	}

	void CSound::Pause(){	

	}

	bool CSound::loadOGG(CString fileName, UGKSND_SoundType &buffer, ALenum &format, ALsizei &freq){
		int endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
		int bitStream;
		long bytes;
		char array[BUFFER_SIZE];    // Local fixed size array
		FILE *f;

		CT2A fileN(fileName);
		// Open for binary reading
		f = fopen(fileN.m_psz, "rb");
		if(!f){
			cout << "Error abriendo '" << fileName << endl;
			return false;
		}

		vorbis_info *pInfo;
		OggVorbis_File oggFile;

		ov_open(f, &oggFile, NULL, 0);
		if(!f) return false;
		// Get some information about the OGG file

		pInfo = ov_info(&oggFile, -1);

		// Check the number of channels... always use 16-bit samples
		if (pInfo->channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		// end if

		// The frequency of the sampling rate
		freq = pInfo->rate;

		do {
			// Read up to a buffer's worth of decoded sound data
			bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
			// Append to end of buffer
			buffer.insert(buffer.end(), array, array + bytes);
		} while (bytes > 0);

		ov_clear(&oggFile);
		return true;
	}
#elif defined(UGKSND_SDL)

/**
*	\fn void CSound::Play(Mix_Chunk *Sound, int vol)
*	Plays the own Sound
*	\param[in] vol Volume to play this sound
*/
void CSound::Play(int vol)
{	

}

/**
*	\fn void CSound::Play()
*	Plays the own Sound with its default volume
*/
void CSound::Play()
{	

}

/**
*	\fn CSound::PlayChannel(int channel, int loops)
*	\brief Plays a sample in a channel
*	\param[in] channel The channel
*	\param[in] loops The number of loops (0 is none, -1 is infinite, other is the number of loops)
*/
void CSound::PlayChannel(int channel, int loops) {

}


/**
*	\fn bool CSound::SetVolume2(int V)
*	\brief Setter of the volume of the sample
*	\param[in] V The volume
*	\return True or False result
*/
bool CSound::SetVolume2(int V) {
	return false;
}

/**
*	\fn CSound::SetVolume()
*	\brief Set the volume of one channel
*/
bool CSound::SetVolume2() {
	return false;
}

#endif

/**
*	\fn void CSound::setVolume(int v)
*	Sets a new Volume
*	\param[in] v New volume to the sound
*/
void CSound::SetVolume(int vol)
{

}

/**
*	\fn void CSound::Init(CString P,int v, CString c)
*	Loads a given sound
*	\param[in] P The name of the sound
*	\param[in] v The volume of the sound
*	\param[in] c The path to the directory of the sound
*/
bool CSound::Init(UGKS_String name, int vol, UGKS_String path)
{

	SetName (name);
	SetPath (path);
	
	Position=0; //Reset to the very beginning of the sound

#ifdef UGKSND_FMOD375 
	//Sound = FSOUND_Stream_Open(aux, 0, Position, 0);
	Sound = FSOUND_Sample_Load(FSOUND_FREE, aux.c_str(), FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, 0, 0);
#elif defined(UGKSND_FMODEx)
	/// Complete
#elif defined(UGKSND_OAL)
	// Create sound buffer and source
	alGenBuffers(1, &bufferID);
	alGenSources(1, &sourceID);

	// Set the source and listener to the same location. THIS CAN BE CHANGED TO IMPLEMENT DIFFERENT POSITIONS
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(sourceID[j], AL_POSITION, 0.0f, 0.0f, 0.0f);

	if(loadOGG(aux, Sound, format, freq)==false) return false;

	// Upload sound data to buffer
	alBufferData(bufferID, format, &Sound[0], static_cast<ALsizei> (bufferData.size()), freq);
	// Attach sound buffer to source
	alSourcei(sourceID, AL_BUFFER, bufferID);

	// All ready: sourceID will be the main variable now
#elif defined(UGKSND_SDL)
	/* Load the WAV */
	UGKS_String FullPath;

	UGKS_GenerateFullPathName(FullPath, Path, Name);
	if ((Sound = Mix_LoadWAV(FullPath.c_str())) == NULL)
		fprintf(stderr, "Could not open %s: %s\n", Name.c_str(), SDL_GetError());
	SetVolume(vol);
	return NULL != Sound;

#endif
	//Sound loaded. Proceed
	SetVolume(vol);

	return true;
}

/**
*	\fn void CSound::close()
*	Close the stream of the sound
*/
void CSound::Close(){

}
/**
*	\fn CSound::Stop()
*	\brief Stop a specified channel
*	\return True or false result
*/

bool CSound::Stop() {
	return false;
}


/**
*	\fn CSound::Resume()
*	\brief Resume a channel
*	\return True or false result
*/

bool CSound::Resume() {
	return false;
}


/**
*	\fn CSound::Expire( int ticks)
*	\brief Expire a channel after some time
*	\param[in] ticks The number of ticks to wait
*/

void CSound::Expire(int ticks) {

}

/**
*	\fn CSound::Pause()
*	\brief Pause a channel
*/

bool CSound::Pause() {
	return false;
}