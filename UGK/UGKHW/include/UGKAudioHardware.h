/**	Definition of the class UGKAudioHardware. Base class for all audio hardware in the system
*
*	Prefix: UGKSNDHW_
*
*	@file	UGKAudioHardware.h
*	@brief	Base class for all audio hardware in the system
*	@author Leopoldo Pla
*	@date	2015-01-28
*   @version Carlos Pérez 2016-01-27
*   @NewVersion Ramón Mollá 2017-12
*
*/

#ifndef UGKSNDHW_HARDWARE
#define UGKSNDHW_HARDWARE

///Include the parent class, the constant definition of sound engines and the UGK header
#include <UGKHardware.h>
#include <UGKSoundEngine.h>

#define UGKSNDHW_NO_CHANNEL -1
#define UGKSNDHW_ERROR		 0

typedef enum
{
	UGKSNDHW_CLOSED,		//The audio subsystem is not activated
	UGKSNDHW_INITIALIZED,	//The audio subsystem has been initialized
	UGKSNDHW_OPENED,		//The current audio device is opened
	UGKSNDHW_PAUSED,		//The current audio device is paused, not stoped
	UGKSNDHW_MAX_STATES
} UGKSNDHW_STATES;

#ifdef UGKSND_FMOD375
	typedef unsigned char Uint8;
	typedef signed char Sint8;
	typedef unsigned short Uint16;
	typedef signed short Sint16;

	#define UGKSND_SoundType FSOUND_SAMPLE*
	#define UGKSND_MusicType FMUSIC_MODULE*

	class CChannel
	{
		int Frequency;
	};
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_FMODStudio)
#elif defined(UGKSND_OAL)
	typedef unsigned char Uint8;
	typedef signed char Sint8;
	typedef unsigned short Uint16;
	typedef signed short Sint16;

	#define UGKSND_SoundType int
	#define UGKSND_MusicType int
#elif defined(UGKSND_SDL)
	#define UGKSND_SoundType Mix_Chunk*
	#define UGKSND_MusicType Mix_Music*

	#define UGKSND_PLAY_BACK_DEVICES	0
	#define UGKSND_RECORDING_DEVICES	1

#endif

#define UGKSND_NO_SAMPLING_FREQ -1

///We work at UGK namespace
namespace UGK
{
	/**
	*	UGKAudioHardware
	*
	*	Manages all the information relative to audio hardware.
	*	It is implemented as a singleton. This is not the game singleton.
	*/

	class UGK_API UGKAudioHardware : public CHardware
	{
	public:
		///Atributes
		/// Type of hardware: main SoundCard, secondary SoundCard... Device number
		UGKSNDHW_STATES		State;

		UGKS_String Name;		///< Name given by the maker API to its sound card
		int SamplingFreq,		///< Sampling frequency at which the hardware is operating
			Format,				///< The way every sample is coded
			Samples;			///< Buffer length
		unsigned char Channels;	///< Amount of hw channels used to output the sound

		///Definition of the type "music" and "sound" effect depending of the sound engine
#ifdef UGKSND_FMOD375
		vector<CChannel> Channel;
#elif defined(UGKSND_FMODEx)
#elif defined(UGKSND_OAL)
#elif defined(UGKSND_SDL)
		SDL_AudioDeviceID	AudioDevice;
		SDL_AudioSpec		Specs;
#endif
		///Audio Hardware management methods

		///General
		UGKAudioHardware();
		~UGKAudioHardware();

		//Virtual methods redefined
		UGKS_String		getProperties();	///Get audioHardware properties
		
		/**
		*	\fn CHW_HW_STATUS UGKAudioHardware::Init()
		*	\brief Initializes the sound system
		*/

		CHW_HW_STATUS	Init();
		CHW_HW_STATUS	Init(long int frequency, int numSoftwareChannels, int flags);

		void Close();

		bool	CheckAudioFormat();
		bool	CheckNumHWChannels();
		int		GetNumHWChannels();
		int		GetNumSWChannels();
		int		GetNumChannelsPlaying();
		int		GetChannelFrequency(int);

		///Samples
		int		GetNumSampleDecoders();
		UGKSND_SoundType *GetSampleDecoder(int);
		const char *GetSampleDecoderName(int);
		bool	SetSampleDefaults(UGKSND_SoundType, int, int, int, int);
		void	DeleteSample(UGKSND_SoundType);
		void	SetSampleLoopPoints(UGKSND_SoundType, int, int);

		///Channels
		void AllocateChannels(int);
		bool RemoveChannelLoop(int);
		void PlayChannelTimed(int, UGKSND_SoundType, int, int);
		void FadeInChannel(int, UGKSND_SoundType, int, int);
		void FadeInChannelTimed(int, UGKSND_SoundType, int, int, int);
		void FadeOutChannel(int, int);
		void SetChannelFinishedFunction(void(*channel_finished)(int channel));
		bool IsChannelPlaying(int);
		bool IsChannelPaused(int);


		///Groups
		int ReserveChannels(int);
		void checkReservedChannels();
		bool GroupChannel(int, int);
		int GroupChannel(int, int, int);
		int GroupCount(int);
		int GroupFindAvailable(int);
		int FadeOutGroup(int, int);
		void HaltGroup(int);


		///Music
		int GetNumMusicDecoders();
		const char* GetMusicDecoder(int index);
		UGKSND_MusicType LoadMusic(const UGKS_String);
		void FreeMusic(UGKSND_MusicType);
		void PlayMusic(UGKSND_MusicType, int);
		bool RemoveMusicLoop(UGKSND_MusicType);
		bool SetMasterMusicSpeed(UGKSND_MusicType, float);
		int  GetMasterMusicSpeed(UGKSND_MusicType);
		void FadeInMusic(UGKSND_MusicType, int, int);
		void FadeInMusicPosition(UGKSND_MusicType, int, int, double);
		void HookMusic(void(*mix_func)(void *udata, Uint8 *stream, int len), void *arg);
		void SetVolumeMusic(UGKSND_MusicType, int);
		int	 GetMasterVolumeMusic(UGKSND_MusicType);
		int	 GetGlobalVolumeMusic(UGKSND_MusicType);
		void PauseMusic(UGKSND_MusicType);
		void RewindMusic();
		void SetMusicPosition(double);
		void SetMusicCommand(const char*);
		void StopMusic(UGKSND_MusicType);
		void StopAllSongs();
		void FadeOutMusic(int);
		void SetMusicFinishedFunction(void(*music_finished)());
		bool IsMusicPlaying(UGKSND_MusicType);
		int  GetMusicTime(UGKSND_MusicType);
		int  GetMusicBPM(UGKSND_MusicType);
		bool IsMusicPaused(UGKSND_MusicType);
		bool IsMusicFinished(UGKSND_MusicType);


		///Normal Effects
		bool SetPanning(int, Uint8, Uint8); /// Channel, left, right
		bool SetDistance(int, Uint8); /// Channel, distance
		bool SetPosition(int, Sint16, Uint8); /// Channel, angle, distance
		bool SetReverseStereo(int, int);

		/// FX
		int  EnableFX(int, int); /// Channel, FxMode
		bool DisableFX(int); /// Channel, FxMode
		bool SetChorusFX(int, float, float, float, float, int, float, int);
		bool SetCompressorFX(int, float, float, float, float, float, float);
		bool SetDistortionFX(int, float, float, float, float, float);
		bool SetEchoFX(int, float, float, float, float, int);
		bool SetFlangerFX(int, float, float, float, float, int, float, int);
		bool SetGargleFX(int, int, int);
		bool SetI3DL2ReverbFX(int, int, int, float, float, float, int, float, int, float, float, float, float);
		bool SetParamEQFX(int, float, float, float);
		bool SetWavesReverbFX(int, float, float, float, float);
	};
}
#endif

