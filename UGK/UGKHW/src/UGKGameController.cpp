/**
*	Class GameController
*	Class prefix: GC_

*	@author Pau Baquero
*	@version 2017
*/

#include <UGKGameController.h>

using namespace UGK;

/**
* @fn CGameController::CGameController(int id)
* Constructor for the game controller. Returns a CGameController
* which needs to be initialized calling its Init()
* before it's used.
*/
CGameController::CGameController(int id) {
	device_index = id;
	TypeHW = CHW_IN_GAMECONTROLLER;		// Define Type Hardware
	SubTypeHW = CHW_IN_GAMECONTROLLER;	// Define SubType GameController
	Status = CHW_HW_ACTIVE;		// Define Active GameController
	vibration = false;			
}

/**
* @fn CGameController::~CGameController()
* Destruct CGameController
*/
CGameController::~CGameController() {
	if (sdl_controller && SDL_GameControllerGetAttached(sdl_controller))
		SDL_GameControllerClose(sdl_controller);
}

/**
* @fn CGameController::Init()
* Init GameController.
* Returns CHW_HW_INITIALIZED if able to initialize,
* CHW_HW_NOT_INITIALIZED elsewhere
*/
CHW_HW_STATUS CGameController::Init() {
	sdl_controller = SDL_GameControllerOpen(device_index);
	if (sdl_controller)
		return CHW_HW_INITIALIZED;
	else
		return CHW_HW_NOT_INITIALIZED;
}

/**
* @fn CGameController::findHardware
* Find hardware game controlker. Returns CHW_HW_NOT_FOUND if not attached.
* Has to be called after Init().
*/
CHW_HW_STATUS CGameController::findHardware() {
	if (NULL == sdl_controller)
		if (SDL_GameControllerGetAttached(sdl_controller) == SDL_TRUE)
			return CHW_HW_ACTIVE;

	return CHW_HW_NOT_FOUND;
}

/**
* @fn CGameController::getAxis
* Get the state of a given axis.
*/
Sint16 CGameController::getAxis(SDL_GameControllerAxis axis) {
	return SDL_GameControllerGetAxis(sdl_controller, axis);
}

/**
* @fn CJoystick::getAxis
* Get the state of a given button.
*/
Uint8 CGameController::getButton(SDL_GameControllerButton button) {
	return SDL_GameControllerGetButton(sdl_controller, button);
}

/**
* @fn CGameController::getJoystick
* Get an equivalent (underlaying in SDL) Joystick.
* It doesn't require initialization.
*/
CJoystick CGameController::getJoystick() {
	return CJoystick(SDL_GameControllerGetJoystick(sdl_controller));
}

/**
* @fn CGameController::getGameControllers
* Returns a list of CGameControllers, one for each connected.
* Remember to Init() each one you want to use before using it.
*/
std::list<CGameController> CGameController::getGameControllers() {
	std::list<CGameController> gcs;
	int i = -1;
	int n = SDL_NumJoysticks();
	while (++i < n)
		if (SDL_IsGameController(i))
			gcs.push_back(CGameController(i));
	return gcs;
}

/**
* @ fn CJoystick::InitSubSystem
* This must be called before using any of the code
* of this class at all.
*/
CHW_HW_STATUS CGameController::InitSubSystem() {
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
	return CHW_HW_INITIALIZED;
}
