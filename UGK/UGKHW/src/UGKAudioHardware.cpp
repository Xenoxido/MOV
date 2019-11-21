/**	Definition of the class UGKAudioHardware. Base class for all audio hardware in the system
*
*	Prefix: UGKSNDHW_
*
*	@file	UGKAudioHardware.h
*	@brief	Base class for all audio hardware in the system
*	@author Leopoldo Pla
*	@date	2015-01-28
*   @NewVersion Carlos Pérez Estruch 2016-01-27
*
*/

/**
* Comentario de Carlos Pérez Estruch a fecha de 27-01-2016:
*
* Entre las apis previstas para añadir al wrapper:
*
* FMOD375 tiene implementada en gran parte la funcionalidad normal y completamente la fx. Falta global3D, streaming, CD audio y reverb básica (se tiene fx por lo que realmente no es necesaria).
* Se han obviado aquellos métodos aparentemente inservibles.
*
* FMODEx no tiene disponible un fichero de cabecera y/o librería para añadir al UGK actualmente.
*
* FMODStudio no tiene disponible un fichero de cabecera y/o librería para añadir al UGK actualmente.
*
* OpenAL no está incluida a fecha de hoy, es un api difícil de entender por lo que se recomienda
* utilizar un mixer (ALmixer) al estilo de SDL (SDLMixer). Almixer combina funcionalidad de OpenAL con
* SDL.
*
* SDL se implementó anteriormente a este comentario y está implementada al completo según la funcionalidad que ofrece.
*
* Algunas consideraciones sobre FMOD: No permite modificación dinámica de canales software de base; Soporta muy pocos
* formatos de tipo música (ver FMUSIC_TYPES); No permite utilizar más de un efecto FX a la vez en un canal.
*/

///Include the header of the class
#include <UGKAudioHardware.h>
#include <vector>

///We use the UGK namespace to make the code cleaner
using namespace UGK;
using namespace std;

UGKAudioHardware::UGKAudioHardware()
{
	SubTypeHW = CHW_SND_MAX_DEVICE; TypeHW = CHW_SOUND;	State = UGKSNDHW_CLOSED; Init();
}

UGKAudioHardware::~UGKAudioHardware(){
#ifdef UGKSND_FMOD375
	FSOUND_Close();
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)
	ALCcontext *context = alcGetCurrentContext();
	ALCdevice *device = alcGetContextsDevice(context);
	alcDestroyContext(context);
	alcCloseDevice(device);
#elif defined(UGKSND_SDL)
	SDL_CloseAudioDevice(AudioDevice);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif
}


CHW_HW_STATUS	UGKAudioHardware::Init()
{
	return Init(UGKSNDENG_FREQ_CD, 2, 0);
}

/**
*	\fn CHW_HW_STATUS UGKAudioHardware::Init()
*	\brief Initializes the sound system
*/

CHW_HW_STATUS UGKAudioHardware::Init(long int frequency, int SoftwareChannels, int flags)
{
	char * msg;
	int Result;

	switch (State)
	{
	case UGKSNDHW_CLOSED:		//The audio subsystem is not activated

#ifdef UGKSND_FMOD375
		if (FSOUND_Init(frequency, SoftwareChannels, flags))
		{
			Status = CHW_HW_ACTIVE;
			State = UGKSNDHW_OPENED;
			return CHW_HW_INITIALIZED;
		}
		else
		{
			Active = false;
			return CHW_HW_NOT_INITIALIZED;
		}
#elif defined(UGKSND_FMODEx)
		return CHW_HW_NOT_INITIALIZED;
#elif defined(UGKSND_FMODStudio)
		return CHW_HW_NOT_INITIALIZED;
#elif defined(UGKSND_OAL)
		ALCdevice *device = alcOpenDevice(NULL);
		ALCcontext *context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);

		TO DO
#elif defined(UGKSND_SDL)
		Result = SDL_InitSubSystem(SDL_INIT_AUDIO);
#ifdef _DEBUG
		if (SND_ERR_NONE != Result)
		{
			printf("SDL audio subsystem initialization failed: %s\n", SDL_GetError());
			exit(UGK_SDL_MIX_OPEN_AUDIO_ERROR);
		}
		State = UGKSNDHW_INITIALIZED;

#endif
	case UGKSNDHW_INITIALIZED:	//The audio subsystem has been initialized
		#ifdef UGKSND_FMOD375
		#elif defined(UGKSND_FMODEx)
		#elif defined(UGKSND_FMODStudio)
		#elif defined(UGKSND_OAL)
		#elif defined(UGKSND_SDL)

			SDL_AudioSpec want, have;

			SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
			want.freq = frequency;
			want.format = AUDIO_S16SYS;
			want.channels = SoftwareChannels;
			want.samples = 4096;
			want.callback = NULL;  // you wrote this function elsewhere.

			AudioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

			Result = SDL_GetNumAudioDevices(UGKSND_PLAY_BACK_DEVICES);
			if (Result > 0)	//-1 means not determined
				if (0 <= AudioDevice)
					if (Result <= AudioDevice)
						AudioDevice = Result - 1;	//Preventing malfunction. Sometimes it happens
			Name = SDL_GetAudioDeviceName(AudioDevice, UGKSND_PLAY_BACK_DEVICES);		///< Name given by the maker API to its sound card

			//Device starts always in SDL in Paused State. So now its state had to be UGKSNDHW_PAUSED
			SDL_PauseAudioDevice(AudioDevice, false); // start audio playing if it has somtehing playing. State = UGKSNDHW_OPENED;
			
			SamplingFreq = have.freq;		///< Sampling frequency at which the hardware is operating
			Format = have.format;			///< The way every sample is coded
			Samples = have.samples;			///< Buffer length
			Channels = have.channels;	//
		#endif
		
		
#ifdef _DEBUG
		if (UGKSNDHW_ERROR == AudioDevice)
		{
			msg = (char*)SDL_GetError();
			printf("Failed to open audio: %s\n", msg);
		}
#endif
		break;
	case UGKSNDHW_OPENED:
		break;
	}

	State = UGKSNDHW_OPENED;
	Status = CHW_HW_ACTIVE;
	return CHW_HW_INITIALIZED;
#endif
}

void UGKAudioHardware::Close()
{
#ifdef UGKSND_FMOD375
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_FMODStudio)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
	SDL_CloseAudioDevice(AudioDevice);
#endif
}

UGKS_String UGKAudioHardware::getProperties(){

	UGKS_String properties = "nothing";
	int nHWChan =  GetNumHWChannels();
	int	nSWChan = GetNumSWChannels();

	properties = "canales hardware: " + std::to_string(nHWChan) + "," + "canales software: " +std::to_string(nSWChan);
	return properties;
}

/**
*	\fn bool UGKAudioHardware::checkNumHWChannels()
*	\brief Print the num of HW channels. This method did not work if we select in configuration Dynamic Library (DLL).
*	\return True or false if error
*/

bool UGKAudioHardware::CheckNumHWChannels(){

#ifdef UGKSND_FMOD375
	int HW2Dchannels, HW3Dchannels, HWChannels;

	if (!FSOUND_GetNumHWChannels(&HW2Dchannels, &HW3Dchannels, &HWChannels)){
		printf("FSOUND_GetNumHWChannels: %s\n", FSOUND_GetError());
		return false;
	}
	else{
		printf("HWchannels=%d HW_2D_channels=%d HW_3D_channels=%d",
			HWChannels, HW2Dchannels, HW3Dchannels);
		return true;
	}
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif
}

/**
*	\fn int UGKAudioHardware::GetNumHWChannels()
*	\brief Get the num of HW channels. This method did not work if we select in configuration Dynamic Library (DLL).
*	\return Number HW channels
*/

int UGKAudioHardware::GetNumHWChannels(){

#ifdef UGKSND_FMOD375
	int HW2Dchannels, HW3Dchannels, HWChannels;

	if (!FSOUND_GetNumHWChannels(&HW2Dchannels, &HW3Dchannels, &HWChannels)){
		printf("FSOUND_GetNumHWChannels: %s\n", FSOUND_GetError());
		return 0;
	}
	else{
		return HWChannels;
	}

#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return 0;
#endif

}

/**
*	\fn int UGKAudioHardware::GetNumSWChannels(int numchannels)
*	\brief Get the num of software channels
*	\return Number SW channels
*/

int UGKAudioHardware::GetNumSWChannels(){
#ifdef UGKSND_FMOD375
	return FSOUND_GetMaxChannels();
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Specs.channels;
#endif
}

/**
*	\fn int UGKAudioHardware::GetNumChannelsPlaying()
*	\brief Get the num of channels playing
*	\return Number of channels playing
*/

int UGKAudioHardware::GetNumChannelsPlaying(){
#ifdef UGKSND_FMOD375
	return FSOUND_GetChannelsPlaying();
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return UGKSNDHW_NO_CHANNEL;
#endif
}

/**
*	\fn bool UGKAudioHardware::CheckChannelFrequency(int channel)
*   \param[in] channel Number of channel
*	\brief Print the frequency of a specified channel
*   \return True or false result
*/

int UGKAudioHardware::GetChannelFrequency(int channel)
{

#ifdef UGKSND_FMOD375
	
	Channel[channel].Frequency = FSOUND_GetFrequency(channel);
	if (!Channel[channel].Frequency)
		printf("FSOUND_GetFrequency: %s\n", FSOUND_GetError());
	
	return Channel[channel].Frequency;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	int numtimesopened, channels;
	numtimesopened = Mix_QuerySpec(&Specs.freq, &Specs.format, &channels);

	if (numtimesopened) 
		return Specs.freq;
	else {
		printf("Mix_QuerySpec: %s\n", SDL_GetError());
		return false;
	}
#endif
}

/**
*	\fn bool UGKAudioHardware::CheckAudioFormat()
*	\brief Print the format of the audio system
*   \return True or false if error
*/

bool UGKAudioHardware::CheckAudioFormat(){
#ifdef UGKSND_FMOD375
	return false;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	// get and print the audio format in use
	int numtimesopened, frequency, channels;
	Uint16 format;
	numtimesopened = Mix_QuerySpec(&frequency, &format, &channels);
	if (!numtimesopened) {
		printf("Mix_QuerySpec: %s\n", SDL_GetError());
		return false;
	}
	else {
		char *format_str = "Unknown";
		switch (format) {
		case AUDIO_U8: format_str = "U8"; break;
		case AUDIO_S8: format_str = "S8"; break;
		case AUDIO_U16LSB: format_str = "U16LSB"; break;
		case AUDIO_S16LSB: format_str = "S16LSB"; break;
		case AUDIO_U16MSB: format_str = "U16MSB"; break;
		case AUDIO_S16MSB: format_str = "S16MSB"; break;
		}
		printf("opened=%d times  frequency=%dHz  format=%s  channels=%d",
			numtimesopened, frequency, format_str, channels);
	}
	return true;
#endif

}

/**
*	\fn UGKAudioHardware::GetNumSampleDecoders()
*	\brief Return the number of decoders per sample
*	\return Number of sample decoders
*/

int UGKAudioHardware::GetNumSampleDecoders(){
#ifdef UGKSND_FMOD375
	return FSOUND_GetMaxSamples();
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_GetNumChunkDecoders();
#endif
}

/**
*	\fn const char* UGKAudioHardware::GetSampleDecoder(int num)
*	\brief Gives one sample decoder
*	\param[in] num Number of decoder
*	\return The sample decoder
*/

UGKSND_SoundType * UGKAudioHardware::GetSampleDecoder(int num)
{
#ifdef UGKSND_FMOD375
	return FSOUND_Sample_Get(num);
#elif defined(UGKSND_FMODEx)
	return NULL;
#elif defined(UGKSND_FMODStudio)
	return NULL;
#elif defined(UGKSND_OAL)
	return NULL;
#elif defined(UGKSND_SDL)
	return NULL;
#endif
}

/**
*	\fn const char* UGKAudioHardware::GetSampleDecoderName(int num)
*	\brief Gives the name of one sample decoder
*	\param[in] num Number of decoder
*	\return The name of the decoder
*/

const char* UGKAudioHardware::GetSampleDecoderName(int num)
{
#ifdef UGKSND_FMOD375
	FSOUND_SAMPLE *sptr = FSOUND_Sample_Get(num);
	return FSOUND_Sample_GetName(sptr);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	return Mix_GetChunkDecoder(num);
#endif
}

/**
*	\fn UGKAudioHardware::SetSampleDefaults(UGKSND_SoundType sample, int frequency, int volume, int pan, int pri)
*	\brief Setter defaults of the sample
*	\param[in] sample The sample, frequency Frequency of the sample
*	\param[in] frequency The Frequency
*	\param[in] volume The volume
*	\param[in] pan The pan
*	\param[in] pri The pri
*	\return True or False result
*/

bool UGKAudioHardware::SetSampleDefaults(UGKSND_SoundType sample, int frequency, int volume, int pan, int pri){
#ifdef UGKSND_FMOD375
	return FSOUND_Sample_SetDefaults(sample, frequency, volume, pan, pri);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (!Mix_VolumeChunk(sample, volume)){
		return false;
	}
	return true;
#endif
}

/**
*	\fn UGKAudioHardware::DeleteSample(UGKSND_SoundType sample)
*	\brief Delete the sample from memory
*	\param[in] sample The sample
*/

void UGKAudioHardware::DeleteSample(UGKSND_SoundType sample){
#ifdef UGKSND_FMOD375
	FSOUND_Sample_Free(sample);
	sample = NULL;
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FreeChunk(sample);
	sample = NULL;
#endif

}

/**
*	\fn UGKAudioHardware::SetSampleLoopPoints(UGKSND_SoundType sample,  int loopstart, int loopend)
*	\brief Set the loop points for a sample
*	\param[in] sample The sample
*	\param[in] loopstart The loopstart point
*	\param[in] loopend The loopend point
*/

void UGKAudioHardware::SetSampleLoopPoints(UGKSND_SoundType sample, int loopstart, int loopend){
#ifdef UGKSND_FMOD375
	FSOUND_Sample_SetLoopPoints(sample, loopstart, loopend);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)

#endif

}

/**
*	\fn UGKAudioHardware::AllocateChannels(int numchannels)
*	\brief Change dynamically the number of channels
*	\param[in] numchannels Number of channels to allocate
*/

void UGKAudioHardware::AllocateChannels(int numchannels){
#ifdef UGKSND_FMOD375
	// FMOD no dispone de un método para cambiar el num. de canales software de forma dinámica.
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_AllocateChannels(numchannels);
#endif
}

/**
*	\fn UGKAudioHardware::RemoveChannelLoop(int channel, UGKSND_SoundType sample, int loops)
*	\brief Take off the loop of a channel
*	\param[in] channel The channel
*	\return True or false if the loop was activated
*/

bool UGKAudioHardware::RemoveChannelLoop(int channel){
#ifdef UGKSND_FMOD375
	return FSOUND_SetLoopMode(channel, FSOUND_LOOP_OFF);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif
}

/**
*	\fn UGKAudioHardware::PlayChannelTimed(int channel, UGKSND_SoundType sample, int loops, int ticks))
*	\brief Plays a sample in a channel after some time
*	\param[in] channel The channel
*	\param[in] sample The sample
*	\param[in] loops The number of loops
*	\param[in] ticks The number of ticks to wait
*/

void UGKAudioHardware::PlayChannelTimed(int channel, UGKSND_SoundType sample, int loops, int ticks){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_PlayChannelTimed(channel, sample, loops, ticks);
#endif
}

/**
*	\fn UGKAudioHardware::FadeInChannel(int channel, UGKSND_SoundType sample, int loops, int ms)
*	\brief Plays a channel with a fade in
*	\param[in] channel The channel
*	\param[in] sample The sample
*	\param[in] loops The number of loops
*	\param[in] ms The miliseconds
*/

void UGKAudioHardware::FadeInChannel(int channel, UGKSND_SoundType sample, int loops, int ms){
#ifdef UGKSND_FMOD375
	// Esta función debería ser llamada con un nuevo thread
	int vol = 0;

	if (loops > 0){
		FSOUND_SetLoopMode(channel, FSOUND_LOOP_NORMAL);
	}

	FSOUND_SetVolume(channel, vol);

	while (vol <= 256){
		FSOUND_SetVolume(channel, vol);
		Sleep(ms / 51);
		vol += 5;
	}
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FadeInChannel(channel, sample, loops, ms);

#endif
}

/**
*	\fn UGKAudioHardware::FadeInChannelTimed(int channel, UGKSND_SoundType sample, int loops, int ms, int ticks)
*	\brief Plays a channel with a fade in
*	\param[in] channel The channel
*	\param[in] sample The sample
*	\param[in] loops The number of loops
*	\param[in] ms The miliseconds
*	\param[in] ticks The number of ticks to wait
*/

void UGKAudioHardware::FadeInChannelTimed(int channel, UGKSND_SoundType sample, int loops, int ms, int ticks){
#ifdef UGKSND_FMOD375
	// Esta función debería ser llamada con un nuevo thread
	Sleep(ticks);
	int vol = 0;

	if (loops > 0){
		FSOUND_SetLoopMode(channel, FSOUND_LOOP_NORMAL);
	}

	FSOUND_SetVolume(channel, vol);

	while (vol <= 256){
		FSOUND_SetVolume(channel, vol);
		Sleep(ms / 51);
		vol += 5;
	}
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FadeInChannelTimed(channel, sample, loops, ms, ticks);
#endif
}


/**
*	\fn UGKAudioHardware::FadeOutChannel(int channel, int ms)
*	\brief Fade out a channel. This function should be called with a new thread.
*	\param[in] channel The channel
*	\param[in] ms The time in miliseconds
*/

void UGKAudioHardware::FadeOutChannel(int channel, int ms){
#ifdef UGKSND_FMOD375
	int vol = FSOUND_GetVolume(channel);

	while (vol >= 0){
		FSOUND_SetVolume(channel, vol);
		Sleep(ms / 51);
		vol -= 5;
	}
	FSOUND_StopSound(channel);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FadeOutChannel(channel, ms);

#endif
}

/**
*	\fn UGKAudioHardware::SetChannelFinishedFunction(void (*channel_finished)(int channel))
*	\brief Set a function to be executed when the channel finishes
*	\param[in] channel_finished The function
*	\param[in] channel The number of channel
*/

void UGKAudioHardware::SetChannelFinishedFunction(void(*channel_finished)(int channel)){
#ifdef UGKSND_FMOD375
	/// FMOD doens't need this function.
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_ChannelFinished(channel_finished);

#endif
}

/**
*	\fn UGKAudioHardware::IsChannelPlaying(int channel)
*	\brief Return if the channel is playing
*	\param[in] channel The channel
*	\return True or false if the channel is playing something
*/

bool UGKAudioHardware::IsChannelPlaying(int channel){
#ifdef UGKSND_FMOD375
	return FSOUND_IsPlaying(channel);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return SDL_AUDIO_PLAYING == SDL_GetAudioDeviceStatus(AudioDevice);
#endif

}

/**
*	\fn UGKAudioHardware::IsChannelPaused(int channel)
*	\brief Return if the channel is paused
*	\param[in] channel The channel
*	\return True or false if the channel is paused
*/

bool UGKAudioHardware::IsChannelPaused(int channel){
#ifdef UGKSND_FMOD375
	return FSOUND_GetPaused(channel);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return SDL_AUDIO_PAUSED == SDL_GetAudioDeviceStatus(AudioDevice);
#endif
}

/**
*	\fn UGKAudioHardware::ReserveChannels(int num)
*	\brief Reserve some channels
*	\param[in] num Number of channels
*	\return Return the number of reserved channels (can be lower than the input)
*/

int UGKAudioHardware::ReserveChannels(int num){
#ifdef UGKSND_FMOD375
	int i = 0;
	int num_channel = 0;
	int channels_reserved = 0;
	while (i < num){
		if (!FSOUND_GetReserved(num_channel)){
			FSOUND_SetReserved(num_channel, TRUE);
			channels_reserved++;
			i++;
		}
		if (FSOUND_GetMaxChannels() == num_channel){
			break;
		}
		num_channel++;
	}
	return channels_reserved;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_ReserveChannels(num);

#endif
}

/**
*	\fn UGKAudioHardware::checkReservedChannels()
*	\brief Check and print the channels that are reserved
*/

void UGKAudioHardware::checkReservedChannels(){
#ifdef UGKSND_FMOD375

	int num_channel = 0;

	while (num_channel < FSOUND_GetMaxChannels()){
		if (FSOUND_GetReserved(num_channel)){
			printf("%d ", num_channel);
		}
	}

	printf("/n");

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)

#endif
}

/**
*	\fn UGKAudioHardware::GroupChannel(int which, int tag)
*	\brief Group channel into a tag
*	\param[in] which The channel
*	\param[in] tag The tag
*	\return True or false result
*/

bool UGKAudioHardware::GroupChannel(int which, int tag){
#ifdef UGKSND_FMOD375
	return false;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_GroupChannel(which, tag) > 0)
		return true;
	else
		return false;
#endif
}

/**
*	\fn UGKAudioHardware::GroupChannel(int from, int to, int tag)
*	\brief Group several channels into a group
*	\param[in] from The first channel
*	\param[in] to The last channel
*	\param[in] tag The tag
*	\return The number of elements grouped
*/

int UGKAudioHardware::GroupChannel(int from, int to, int tag){
#ifdef UGKSND_FMOD375
	return 0;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_GroupChannels(from, to, tag);
#endif
}

/**
*	\fn UGKAudioHardware::GroupCount(int tag)
*	\brief Returns the number of channels with a tag
*	\param[in] tag The tag
*	\return The number of channels
*/

int UGKAudioHardware::GroupCount(int tag){
#ifdef UGKSND_FMOD375
	return 0;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_GroupCount(tag);
#endif
}

/**
*	\fn UGKAudioHardware::GroupCount(int tag)
*	\brief Returns the number of channels with a tag
*	\param[in] tag The tag
*	\return The number of channels
*/

int UGKAudioHardware::GroupFindAvailable(int tag){
#ifdef UGKSND_FMOD375
	return 0;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_GroupAvailable(tag);
#endif
}

/**
*	\fn UGKAudioHardware::FadeOutGroup(int tag, int ms)
*	\brief Fade out a group of channels
*	\param[in] tag The tag
*	\param[in] ms The time of fade out
*	\return The number of channels which can do fade out
*/

int UGKAudioHardware::FadeOutGroup(int tag, int ms){
#ifdef UGKSND_FMOD375
	return 0;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_FadeOutGroup(tag, ms);

#endif
}

/**
*	\fn UGKAudioHardware::HaltGroup(int tag)
*	\brief Halt a group of channels
*	\param[in] tag The tag
*/

void UGKAudioHardware::HaltGroup(int tag){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_HaltGroup(tag);
#endif
}

/**
*	\fn UGKAudioHardware::GetNumMusicDecoders()
*	\brief Return the num of decoders for music
*	\return The number of decoders
*/

int UGKAudioHardware::GetNumMusicDecoders(){
#ifdef UGKSND_FMOD375
	return 0;
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_GetNumMusicDecoders();

#endif
}

/**
*	\fn UGKAudioHardware::GetNumMusicDecoders(int index)
*	\brief Return the name of one decoder for music
*	\param[in] index The number of the decoder
*	\return The name of the decoder
*/
const char* UGKAudioHardware::GetMusicDecoder(int index){
#ifdef UGKSND_FMOD375
	return UGKS_EMPTY_STRING;
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	return Mix_GetMusicDecoder(index);

#endif
}

/**
*	\fn UGKAudioHardware::LoadMusic(const char* musicRoute)
*	\brief Load music into memory
*	\param[in] musicRoute The music file path
*	\return The music file in memory
*/

UGKSND_MusicType UGKAudioHardware::LoadMusic(UGKS_String musicRoute){
#ifdef UGKSND_FMOD375
	UGKSND_MusicType music = FMUSIC_LoadSong(musicRoute.c_str());
	if (!music) {
		printf("FMUSIC_LoadSon(\"music.mp3\"): %s\n", FSOUND_GetError());
	}
	return music;
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)

	UGKSND_MusicType music = Mix_LoadMUS(musicRoute.c_str());
	if (!music) {
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", SDL_GetError());
		// this might be a critical error...
	}
	return music;
#endif

}

/**
*	\fn UGKAudioHardware::FreeMusic(UGKSND_MusicType music)
*	\brief Free music from memory
*	\param[in] music The music data
*/

void UGKAudioHardware::FreeMusic(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	FMUSIC_FreeSong(music);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FreeMusic(music);
	music = NULL;
#endif

}

/**
*	\fn UGKAudioHardware::PlayMusic(UGKSND_MusicType music, int loops)
*	\brief Play given music
*	\param[in] music The music data
*	\param[in] loops The number of loops (same as sample)
*/

void UGKAudioHardware::PlayMusic(UGKSND_MusicType music, int loops){
#ifdef UGKSND_FMOD375
	if (loops > 1 || loops ==- 1){
		FMUSIC_SetLooping(music, TRUE);
	}
	FMUSIC_PlaySong(music);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_PlayMusic(music, loops);
#endif
}

/**
*	\fn UGKAudioHardware::RemoveMusicLoop(UGKSND_MusicType music)
*	\brief Remove music loops
*	\param[in] music The music data
*   \return True or False result
*/

bool UGKAudioHardware::RemoveMusicLoop(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_SetLooping(music, FALSE);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif
}

/**
*	\fn UGKAudioHardware::SetMasterMusicSpeed(UGKSND_MusicType music)
*	\brief Remove music loops
*	\param[in] music The music data
*	\param[in] speed The desired master speed
*   \return True or False result
*/

bool UGKAudioHardware::SetMasterMusicSpeed(UGKSND_MusicType music, float speed){
#ifdef UGKSND_FMOD375
	return FMUSIC_SetMasterSpeed(music, speed);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif
}

/**
*	\fn UGKAudioHardware::GetMasterMusicSpeed(UGKSND_MusicType music)
*	\brief Remove music loops
*	\param[in] music The music data
*	\param[in] speed The desired master speed
*   \return True or False result
*/

int UGKAudioHardware::GetMasterMusicSpeed(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetSpeed(music);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif
}

/**
*	\fn UGKAudioHardware::FadeInMusic(UGKSND_MusicType music, int loops, int ms)
*	\brief Fade in music
*	\param[in] music The music data
*	\param[in] loops The loop number
*	\param[in] ms The time to fade in
*/

void UGKAudioHardware::FadeInMusic(UGKSND_MusicType music, int loops, int ms){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FadeInMusic(music, loops, ms);

#endif
}

/**
*	\fn UGKAudioHardware::FadeInMusic(UGKSND_MusicType music, int loops, int ms)
*	\brief Fade in music
*	\param[in] music The music data
*	\param[in] loops The loop number
*	\param[in] ms The time to fade in
*/

void UGKAudioHardware::FadeInMusicPosition(UGKSND_MusicType music, int loops, int ms, double position){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_FadeInMusicPos(music, loops, ms, position);

#endif
}

/**
*	\fn UGKAudioHardware::HookMusic(void (*mix_func)(void *udata, Uint8 *stream, int len), void *arg)
*	\brief Add your own music player or additional mixer function
*	\param[in] mix_func The function
*	\param[in] arg The arguments
*/

void UGKAudioHardware::HookMusic(void(*mix_func)(void *udata, Uint8 *stream, int len), void *arg){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_HookMusic(mix_func, arg);

#endif
}

/**
*	\fn UGKAudioHardware::SetVolumeMusic(UGKSND_MusicType music, int volume)
*	\brief Set music volume
*	\param[in] music The music data
*	\param[in] volume The volume
*/

void UGKAudioHardware::SetVolumeMusic(UGKSND_MusicType music, int volume){
#ifdef UGKSND_FMOD375
	FMUSIC_SetMasterVolume(music, volume);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_VolumeMusic(volume);

#endif
}

/**
*	\fn UGKAudioHardware::GetMasterVolumeMusic(UGKSND_MusicType music)
*	\brief Get master music volume
*	\param[in] music The music data
*	\return The volume of the music
*/

int UGKAudioHardware::GetMasterVolumeMusic(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetMasterVolume(music);
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_VolumeMusic(-1);

#endif
}

/**
*	\fn UGKAudioHardware::GetGlobalVolumeMusic(UGKSND_MusicType music)
*	\brief Get global music volume
*	\param[in] music The music data
*	\return The volume of the music
*/

int UGKAudioHardware::GetGlobalVolumeMusic(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetGlobalVolume(music);
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return Mix_VolumeMusic(-1);

#endif
}

/**
*	\fn UGKAudioHardware::PauseMusic(UGKSND_MusicType music)
*	\brief Pause music
*	\param[in] music The music data
*/

void UGKAudioHardware::PauseMusic(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	FMUSIC_SetPaused(music, TRUE);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_PauseMusic();

#endif
}

/**
*	\fn UGKAudioHardware::RewindMusic()
*	\brief Rewind music
*/

void UGKAudioHardware::RewindMusic(){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_RewindMusic();

#endif
}

/**
*	\fn UGKAudioHardware::SetMusicPosition(double position)
*	\brief Set music position
*	\param[in] position The position
*/

void UGKAudioHardware::SetMusicPosition(double position){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_SetMusicPosition(position);

#endif
}

/**
*	\fn UGKAudioHardware::SetMusicCommand(const char* command)
*	\brief Set music command to stop
*	\param[in] command The command
*/

void UGKAudioHardware::SetMusicCommand(const char* command){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_SetMusicCMD(command);

#endif
}

/**
*	\fn UGKAudioHardware::StopMusic()
*	\brief Stop concrete music
*	\param[in] music The music data
*/

void UGKAudioHardware::StopMusic(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	FMUSIC_StopSong(music);
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_HaltMusic();

#endif
}

/**
*	\fn UGKAudioHardware::StopAllSongs()
*	\brief Stop all music
*/

void UGKAudioHardware::StopAllSongs(){
#ifdef UGKSND_FMOD375
	FMUSIC_StopAllSongs();
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_HaltMusic();

#endif
}

/**
*	\fn UGKAudioHardware::FadeOutMusic(int ms)
*	\brief Fade out music
*	\param[in] ms The time of fade out
*/

void UGKAudioHardware::FadeOutMusic(int ms){
#ifdef UGKSND_FMOD375

#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	while (!Mix_FadeOutMusic(ms) && Mix_PlayingMusic()) {
		// wait for any fades to complete
		SDL_Delay(100);
	}
#endif


}

/**
*	\fn UGKAudioHardware::SetMusicFinishedFunction(void (*music_finished)())
*	\brief Set a function to be executed when a music finishes
*	\param[in] music_finished The function
*/

void UGKAudioHardware::SetMusicFinishedFunction(void(*music_finished)()){
#ifdef UGKSND_FMOD375
	/// FMOD doesn't need it.
#elif defined(UGKSND_FMODEx)

#elif defined(UGKSND_FMODStudio)

#elif defined(UGKSND_OAL)

#elif defined(UGKSND_SDL)
	Mix_HookMusicFinished(music_finished);

#endif
}

/**
*	\fn UGKAudioHardware::IsMusicPlaying()
*	\brief Return if there is music being played
*	\param[in] music The music data
*	\return True or false if music is being played
*/

bool UGKAudioHardware::IsMusicPlaying(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_IsPlaying(music);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_PlayingMusic() > 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::GetMusicTime(UGKSND_MusicType music)
*	\brief Get the time of a music
*	\param[in] music The music data
*	\return The time
*/

int UGKAudioHardware::GetMusicTime(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetTime(music);
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return 0;
#endif
}

/**
*	\fn UGKAudioHardware::GetMusicBPM(UGKSND_MusicType music)
*	\brief Get the bpm of a music
*	\param[in] music The music data
*	\return The bpm
*/

int UGKAudioHardware::GetMusicBPM(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetBPM(music);
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return 0;
#endif
}

/**
*	\fn UGKAudioHardware::IsMusicPaused()
*	\brief Return if there is music paused
*	\param[in] music The music data
*	\return True or false if music is paused
*/

bool UGKAudioHardware::IsMusicPaused(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_GetPaused(music);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_PausedMusic() > 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::IsMusicFinished()
*	\brief Return if there is music paused
*	\param[in] music The music data
*	\return True or false if music is paused
*/

bool UGKAudioHardware::IsMusicFinished(UGKSND_MusicType music){
#ifdef UGKSND_FMOD375
	return FMUSIC_IsFinished(music);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_PlayingMusic() <= 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetPanning(int channel, Uint8 left, Uint8 right)
*	\brief Set panning to channel
*	\param[in] channel The channel
*	\param[in] left The panning of left speaker
*	\param[in] right The panning of right speaker
*	\return True or false if music is panned after all
*/

bool UGKAudioHardware::SetPanning(int channel, Uint8 left, Uint8 right){
#ifdef UGKSND_FMOD375
	return FSOUND_SetPan(channel, right);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_SetPanning(channel, left, right) > 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetDistance(int channel, Uint8 distance)
*	\brief Set distance to channel
*	\param[in] channel The channel
*	\param[in] distance The distance
*	\return True or false if music is distanced after all
*/

bool UGKAudioHardware::SetDistance(int channel, Uint8 distance){
#ifdef UGKSND_FMOD375
	return false;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_SetDistance(channel, distance) > 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetPosition(int channel, Sint16 angle, Uint8 distance)
*	\brief Set a relative position in a channel
*	\param[in] channel The channel
*	\param[in] angle The angle
*	\param[in] distance The distance
*	\return True or false if music is positioned after all
*/

bool UGKAudioHardware::SetPosition(int channel, Sint16 angle, Uint8 distance){
#ifdef UGKSND_FMOD375
	return false;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_SetPosition(channel, angle, distance) > 0)
		return true;
	else
		return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetReverseStereo(int channel, int flip)
*	\brief Set a flip of the speakers in a channel
*	\param[in] channel The channel
*	\param[in] flip Nonzero if you want flip.
*	\return True or false if music is flipped after all
*/

bool UGKAudioHardware::SetReverseStereo(int channel, int flip){
#ifdef UGKSND_FMOD375
	return false;
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	if (Mix_SetReverseStereo(channel, flip) > 0)
		return true;
	else
		return false;
#endif

}

/// FX functions

/**
*	\fn UGKAudioHardware::EnableFX(int channel, int FxMode)
*	\brief Enable an effect in a channel
*	\param[in] channel The channel
*	\param[in] FxMode Fx mode
*	\param[out] fxid Fx ide to modifie the effect later
*	\return Id of effect
*/

int UGKAudioHardware::EnableFX(int channel, int FxMode){
#ifdef UGKSND_FMOD375
	if (FxMode >= SND_FX_MAX){
		printf("Bad Fx definition. Check you choose the correct mode. \n");
		return 0;
	}
	else{
		return FSOUND_FX_Enable(channel, FxMode);
	}
#elif defined(UGKSND_FMODEx)
	return 0;
#elif defined(UGKSND_FMODStudio)
	return 0;
#elif defined(UGKSND_OAL)
	return 0;
#elif defined(UGKSND_SDL)
	return 0;
#endif

}

/**
*	\fn UGKAudioHardware::EnableFX(int channel, int FxMode)
*	\brief Enable an effect in a channel
*	\param[in] channel The channel
*	\param[in] FxMode Fx mode
*	\return bool Result of the action
*/

bool UGKAudioHardware::DisableFX(int channel){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_Disable(channel);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetChorusFX(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase)
*	\brief Set chorus effect
*	\param[in] fxid The id of the effect
*	\param[in] WetDryMix Quantity of original/processed signal
*	\param[in] Depth Signal depth
*	\param[in] Feedback Signal feedback
*	\param[in] Frequency Chorus frequency
*	\param[in] Waveform Chorus waveform
*	\param[in] Delay Chorus delay
*	\param[in] Phase Chorus phase
*	\return True or false Result
*/

bool UGKAudioHardware::SetChorusFX(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetChorus(fxid, WetDryMix, Depth, Feedback, Frequency, Waveform, Delay, Phase);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn UGKAudioHardware::SetCompressorFX(int fxid, float Gain, float Attack, float Release, float Threshold, float Ratio, float Predelay)
*	\brief Set Compressor effect
*	\param[in] fxid The id of the effect
*	\param[in] Gain The gain of the compressor
*	\param[in] Attack The Attack parametter
*	\param[in] Release The Decay parametter
*	\param[in] Threshold The thrshold of the compressor
*	\param[in] Ratio Compression ratio
*	\param[in] Predelay Compressor predelay
*	\return True or false Result
*/

bool UGKAudioHardware::SetCompressorFX(int fxid, float Gain, float Attack, float Release, float Threshold, float Ratio, float Predelay){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetCompressor(fxid, Gain, Attack, Release, Threshold, Ratio, Predelay);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn SetDistortionFX(int fxid, float Gain, float Edge, float PostEQCenterFrequency, float PostEQBandwidth, float PreLowpassCutoff)
*	\brief Set Distortion effect
*	\param[in] fxid The id of the effect
*	\param[in] Gain Distortion Gain
*	\param[in] Edge Distortion Edge
*	\param[in] PostEQCenterFrequency Distortion PostEQCenterFrequency
*	\param[in] PostEQBandwidth Distortion PostEQBandwidth
*	\param[in] PreLowpassCutoff Distortion PreLowpassCutoff
*	\return True or false Result
*/

bool UGKAudioHardware::SetDistortionFX(int fxid, float Gain, float Edge, float PostEQCenterFrequency, float PostEQBandwidth, float PreLowpassCutoff){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetDistortion(fxid, Gain, Edge, PostEQCenterFrequency, PostEQBandwidth, PreLowpassCutoff);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetEchoFX(int fxid, float WetDryMix, float Feedback, float LeftDelay, float RightDelay, int PanDelay)
*	\brief Set Echo effect
*	\param[in] fxid The id of the effect
*	\param[in] WetDryMix Quantity of original/processed signal
*	\param[in] Feedback Signal feedback
*	\param[in] LeftDelay Echo left delay
*	\param[in] RightDelay Echo right delay
*	\param[in] PanDelay Echo pan delay
*	\return True or false Result
*/

bool UGKAudioHardware::SetEchoFX(int fxid, float WetDryMix, float Feedback, float LeftDelay, float RightDelay, int PanDelay){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetEcho(fxid, WetDryMix, Feedback, LeftDelay, RightDelay, PanDelay);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetFlangerFX(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase)
*	\brief Set Flanger effect
*	\param[in] fxid The id of the effect
*	\param[in] WetDryMix Quantity of original/processed signal
*	\param[in] Depth Signal depth
*	\param[in] Feedback Signal feedback
*	\param[in] Frequency Flanger frequency
*	\param[in] Waveform Flanger waveform
*	\param[in] Delay Flanger delay
*	\param[in] Phase Flanger phase
*	\return True or false Result
*/

bool UGKAudioHardware::SetFlangerFX(int fxid, float WetDryMix, float Depth, float Feedback, float Frequency, int Waveform, float Delay, int Phase){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetFlanger(fxid, WetDryMix, Depth, Feedback, Frequency, Waveform, Delay, Phase);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetGargleFX(int fxid, int RateHz, int WaveShape)
*	\brief Set Gargle effect
*	\param[in] fxid The id of the effect
*	\param[in] RateHz 
*	\param[in] WaveShape Gargle waveshape
*	\return True or false Result
*/

bool UGKAudioHardware::SetGargleFX(int fxid, int RateHz, int WaveShape){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetGargle(fxid, RateHz, WaveShape);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetI3DL2ReverbFX(int fxid, int Room, int RoomHF, float RoomRolloffFactor, float DecayTime, float DecayHFRatio, int Reflections, float ReflectionsDelay, int Reverb, float ReverbDelay, float Diffusion, float Density, float HFReference)
*	\brief Set Reverb effect. SEE FMOD api for more info about parametters.
*	\param[in] fxid The id of the effect
*	\param[in] Room Room effect level (at mid frequencies)
*	\param[in] RoomHF Relative room effect level at high frequencies
*	\param[in] RoomRolloffFactor
*	\param[in] DecayTime Reverberation decay time at mid frequencies
*	\param[in] DecayHFRatio High-frequency to mid-frequency decay time ratio
*	\param[in] Reflections Early reflections level relative to room effect
*	\param[in] ReflectionsDelay Initial reflection delay time
*	\param[in] Reverb Late Reverberation level relative to room effect
*	\param[in] ReverbDelay Late reverberation delay time relative to initial reflection
*	\param[in] Diffusion Value that controls the echo density in the late reverberation decay
*	\param[in] Density Value that controls the modal density in the late reverberation decay
*	\param[in] HFReference Reference high frequency (hz)
*	\return True or false Result
*/

bool UGKAudioHardware::SetI3DL2ReverbFX(int fxid, int Room, int RoomHF, float RoomRolloffFactor, float DecayTime, float DecayHFRatio, int Reflections, float ReflectionsDelay, int Reverb, float ReverbDelay, float Diffusion, float Density, float HFReference){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetI3DL2Reverb(fxid, Room, RoomHF, RoomRolloffFactor, DecayTime, DecayHFRatio, Reflections, ReflectionsDelay, Reverb, ReverbDelay, Diffusion, Density, HFReference);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetParamEQFX(int fxid, float Center, float Bandwidth, float Gain)
*	\brief Set ParaEQ
*	\param[in] fxid The id of the effect
*	\param[in] Center ParamEQ center
*	\param[in] Bandwidth ParamEQ bandwith
*	\param[in] Gain ParamEQ gain
*	\return True or false Result
*/

bool UGKAudioHardware::SetParamEQFX(int fxid, float Center, float Bandwidth, float Gain){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetParamEQ(fxid, Center, Bandwidth, Gain);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}

/**
*	\fn bool SetWavesReverbFX(int fxid, float InGain, float ReverbMix, float ReverbTime, float HighFreqRTRatio)
*	\brief Set ParaEQ
*	\param[in] fxid The id of the effect
*	\param[in] InGain Input gain
*	\param[in] ReverbMix Reverb mix
*	\param[in] ReverbTime Reverb time
*	\param[in] HighFreqRTRatio High frequency ratio
*	\return True or false Result
*/

bool UGKAudioHardware::SetWavesReverbFX(int fxid, float InGain, float ReverbMix, float ReverbTime, float HighFreqRTRatio){
#ifdef UGKSND_FMOD375
	return FSOUND_FX_SetWavesReverb(fxid, InGain, ReverbMix, ReverbTime, HighFreqRTRatio);
#elif defined(UGKSND_FMODEx)
	return false;
#elif defined(UGKSND_FMODStudio)
	return false;
#elif defined(UGKSND_OAL)
	return false;
#elif defined(UGKSND_SDL)
	return false;
#endif

}