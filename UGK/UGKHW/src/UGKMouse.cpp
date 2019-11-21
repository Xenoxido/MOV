/**
*	Class Mouse

*	Class prefix: MO_

*	@author Pau Baquero
*	@version 2017
*/

#include <UGKMouse.h>

using namespace UGK;

/**
	* @fn CMouse::CMouse()
	* Constructor for the mouse
*/
CMouse::CMouse() {
}

/**
	* @fn CMouse::~CMouse()
	* Destruct Mouse
*/
CMouse::~CMouse() {
}

/**
	* @fn CMouse::Init
	* Init mouse
*/
CHW_HW_STATUS CMouse::Init() {
	/// Mouse INITIALIZATION
	return CHW_HW_INITIALIZED;
}

/**
* @fn CMouse::findHardware
* Find hardware mouse
*/
CHW_HW_STATUS CMouse::findHardware() {
	return CHW_HW_NOT_FOUND; /// SDL has no way of checking whether a mouse is connected
}

/**
	* @fn CMouse::leftButtonPressed
	* checks whether the left button has been pressed
*/
bool CMouse::leftButtonPressed() {
	int x, y;
	return SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK;
}

/**
* @fn CMouse::rightButtonPressed
* checks whether the right button has been pressed
*/
bool CMouse::rightButtonPressed() {
	int x, y;
	return SDL_GetMouseState(&x, &y) & SDL_BUTTON_RMASK;
}

/**
* @fn CMouse::midButtonPressed
* checks whether the middle button has been pressed
*/
bool CMouse::midButtonPressed() {
	int x, y;
	return SDL_GetMouseState(&x, &y) & SDL_BUTTON_MMASK;
}

/**
* @fn CMouse::wheelUpHappened
* checks whether the wheel has been moved upwards
*/
bool CMouse::wheelUpHappened() {
	int x, y;
	return SDL_GetMouseState(&x, &y) & SDL_BUTTON_UMASK;
}

/**
* @fn CMouse::wheelDownHappened
* checks whether the wheel has been moved downwards
*/
bool CMouse::wheelDownHappened() {
	int x, y;
	return SDL_GetMouseState(&x, &y) & SDL_BUTTON_DMASK;
}
