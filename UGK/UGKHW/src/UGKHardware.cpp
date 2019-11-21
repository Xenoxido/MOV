/**	/**	@file UGKHardware.cpp
	Definition of the class CHardware. Base class for all hardware in the system

*	Prefix: CHW_

*	@author Ramon Molla
	@author David Peris
*	@version 2015-05
*/

#include <UGKHardware.h>

/**
* chars of enum type CHW_HARDWARE_TYPE that belongs to the posible value of the tag NAME in UGKDeviceParser.  
*/

/*
CHW_SOUND,		//Output sound through a sounds card
CHW_GRAPHIC,	//Output video through a graphics card
CHW_IN_KEYBOARD,		///< Device Keyboard
CHW_IN_MOUSE,			///< Device Mouse
CHW_IN_JOYSTICK,		///< Device Joystick
CHW_IN_GAMECONTROLLER,	///< Device Game Controller
CHW_IN_WIIMOTE,			///< Device Wiimote
CHW_IN_KINECT,			///< Device Kinect
CHW_IN_WEBCAM,			///< Device Web Cam
CHW_IN_LEAP,			///< Device Leap Motion
CHW_IN_GLOVE,			///< Device Guante
CHW_IN_GENERIC,			///< Device Generic
CHW_IN_MIC,				///< Device Microphone
CHW_IN_TOUCHSCREEN
*/

char *CHW_HWType[CHW_MAX_HW_TYPE] =
	{
		"",
		"SOUND",		//Output sound through a sounds card
		"GRAPHICS",		//Output video through a graphics card
		"KEYBOARD",		// Device Keyboard
		"MOUSE",		// Device Mouse
		"JOYSTICK",		// Device Joystick
		"GAMECONTROLLER",
		"WIIMOTE",		// Device Wiimote
		"KINECT",		// Device Kinect
		"WEBCAM",		// Device Web Cam
		"LEAP",			// Device Leap Motion
		"GLOVE",		// Device Guante
		"GENERIC",		// Device Generic
		"MIC",			// Device Microphone
		"TOUCHSCREEN"	// Device Touch Screen. For tablets
	};

using namespace UGK;


CHardware::CHardware(){}

/**
	Constructor of the class
**/
CHardware::CHardware(unsigned int type)
{	
	TypeHW = CHW_HARDWARE_TYPE(type);
	Status = CHW_HW_NOT_FOUND;
}

/**
	Destructor of the class
**/
CHardware::~CHardware(){}

//Virutal methods defined by default

/**
*	\fn CHW_HW_STATUS CHardware::Init(void)

*	Initializes the hardware to be used inmediately
*/
CHW_HW_STATUS CHardware::Init(void)
{
	return CHW_HW_NOT_INITIALIZED;
}

/**
*	\fn bool CHardware::findHardware()
*	Search the available hardware
*/
CHW_HW_STATUS CHardware::findHardware(){

	return CHW_HW_NOT_FOUND;
}

/**
*	\fn UGKS_String CHardware::getProperties()
*	Obtains hardware information
*/
 UGKS_String CHardware::getProperties(){

	 UGKS_String properties = "nothing";

	return properties;
}

/**
*	\fn void CHardware::Finish()
*	Obtains hardware information
*/

 void	CHardware::Finish()
 {
 }///Closes the hardware