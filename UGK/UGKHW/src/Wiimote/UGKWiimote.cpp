/**	UGKWiimote.cpp

*	@author Ramon Molla, Imanol Fraile
*	@version 2015-05
*/

//#include "Copyright.h"
#include <cstdio>
#include <Wiimote\UGKWiimote.h>
using namespace UGK;

/**
*	\fn CWiiMote::IsLedSet()
*	\brief WIIUSE_IS_LED_SET is a #define that links a literal number into a string, so we cannot join directlythe name of a variable to that string
*	\param[in] led: The led number of the Wiimote
*/

CWiiMote::CWiiMote(int uid) {
	WiimoteHW = wiiuse_init(1)[0];
	uid = uid;
	TypeHW = CHW_IN_WIIMOTE;		// Define Type Hardware
	Status = CHW_HW_ACTIVE;					// Define Active Keyboard
}


CHW_HW_STATUS CWiiMote::findHardware()
{
	for (int i = 1; i <= 4; i = i++){
		if (CWiiMote::IsLedSet(i)){
			return CHW_HW_NOT_FOUND;
		}
	}
	return CHW_HW_NOT_FOUND;
}

boolean CWiiMote::IsLedSet (int led)
{
	switch(led)
	{
		case 1: return WIIUSE_IS_LED_SET(WiimoteHW,1);
		case 2: return WIIUSE_IS_LED_SET(WiimoteHW,2);
		case 3: return WIIUSE_IS_LED_SET(WiimoteHW,3);
		case 4: return WIIUSE_IS_LED_SET(WiimoteHW,4);
	}
	return false;
}
