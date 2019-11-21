/**
*	Class Joystick
*	Class prefix: JS_

*	@author Pau Baquero
*	@version 2017
*/

#include <UGKJoystick.h>

using namespace UGK;

/**
	* @fn CJoystick::CJoystick(int id)
	* Constructor for the joystick. Returns a CJoystick
	* which needs to be initialized calling its Init()
	* before it's used.
*/
CJoystick::CJoystick(int id) {
	device_index = id;
	TypeHW = CHW_IN_JOYSTICK;		// Define Type Hardware
	SubTypeHW = CHW_IN_JOYSTICK;	// Define SubType Joystick
	Status = CHW_HW_ACTIVE;		// Define Active Joystick
	vibration = false;
	n_buttons = 0;
}

CJoystick::CJoystick(SDL_Joystick* joy) {
	device_index = -1;
	sdl_joystick = joy;
	TypeHW = CHW_IN_JOYSTICK;		// Define Type Hardware
	SubTypeHW = CHW_IN_JOYSTICK;	// Define SubType Joystick
	Status = CHW_HW_ACTIVE;		// Define Active Joystick
	vibration = false;
	n_buttons = 0;
}


/**
	* @fn CJoystick::~CJoystick()
	* Destruct Joystick
*/
CJoystick::~CJoystick() {
	if (sdl_joystick && SDL_JoystickGetAttached(sdl_joystick))
		SDL_JoystickClose(sdl_joystick);
}

/**
	* @fn CJoystick::Init()
	* Init Joystick.
	* Returns CHW_HW_INITIALIZED if able to initialize,
	* CHW_HW_NOT_INITIALIZED elsewhere
*/
CHW_HW_STATUS CJoystick::Init() {
	sdl_joystick = SDL_JoystickOpen(device_index);
	if (sdl_joystick)
		return CHW_HW_INITIALIZED;
	else
		return CHW_HW_NOT_INITIALIZED;
}

/**
	* @fn CJoystick::findHardware
	* Find hardware joystick. Returns CHW_HW_NOT_FOUND if not attached.
	* Has to be called after Init().
*/
CHW_HW_STATUS CJoystick::findHardware() {
	if (NULL == sdl_joystick)
		if (SDL_JoystickGetAttached(sdl_joystick) == SDL_TRUE)
			return CHW_HW_ACTIVE;

	return CHW_HW_NOT_FOUND;
}

/**
* @fn CJoystick::getAxis
* Get the state of a given axis. the axis indices start at index 0.
*/
Sint16 CJoystick::getAxis(int axis) {
	return SDL_JoystickGetAxis(sdl_joystick, axis);
}

/**
* @fn CJoystick::getAxis
* Get the state of a given button. the button indices start at index 0.
*/
Uint8 CJoystick::getButton(int button) {
	return SDL_JoystickGetButton(sdl_joystick, button);
}

/**	
* @fn CJoystick::getHat
* Get the state of a given POV Hat. the Hat indices start at index 0.
*/
Uint8 CJoystick::getHat(int hat) {
	return SDL_JoystickGetHat(sdl_joystick, hat);
}

/**
	* @fn CJoystick::getJoysticks
	* Returns a list of CJoysticks, one for each connected.
	* Remember to Init() each one you want to use before using it.
*/
std::list<CJoystick> CJoystick::getJoysticks() {
	std::list<CJoystick> joys;
	int i = 0;
	int n = SDL_NumJoysticks();
	while (i < n)
		joys.push_back(CJoystick(i++));
	return joys;
}

/**
	* @ fn CJoystick::InitSubSystem
	* This must be called before using any of the code
	* of this class at all.
*/
CHW_HW_STATUS CJoystick::InitSubSystem() {
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	return CHW_HW_INITIALIZED;
}