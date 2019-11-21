/**
*	@file	 UGKDeviceManager.cpp
*	@author  Joan Puigcerver
*	@date	 2017-02
*   @version 1.0
*
*	@modified: Ramón Mollá
*	@brief	Class that manages all HW / devices involved with our application
*
*	Prefix: UGKDM_
**/


#include <thread>
//ACHTUNG: Since liteHTML reader used by UGKDeviceParser calls to afxtempl.h, it has to be the first one before any other call to windows.h 
#include <UGKDeviceManager.h>
#include <UGKHardwareList.h>

using namespace std;
using namespace UGK;

CDeviceManager::CDeviceManager()
{
	hardware_vector.resize(0);
	active_vector.resize(0);
}

CDeviceManager::~CDeviceManager()
{
	hardware_vector.clear();
	active_vector.clear();
}

void UGK::CDeviceManager::pushBack(CHardware *hw)
{
	hardware_vector.push_back(hw);
	active_vector.push_back(false);
}
void UGK::CDeviceManager::deleteHardware(int index)
{
	hardware_vector.erase( hardware_vector.begin() + index );
	active_vector.erase( active_vector.begin() + index );
}

void CDeviceManager::verificationHardware( int i)
{
	if (hardware_vector[i] == NULL)
	{
		active_vector[i] = false;
		return;
	}
	active_vector[i] = CHW_HW_NOT_FOUND != hardware_vector[i]->findHardware();
}

void CDeviceManager::verification()
{
	if (hardware_vector.size() == 0) return;
	std::thread* threads = new std::thread[hardware_vector.size()];
	for (int i = 0; i < hardware_vector.size(); i++)
		threads[i] = std::thread( &CDeviceManager::verificationHardware, this, i);
	for (int i = 0; i < hardware_vector.size(); i++)
		threads[i].join();
	delete[] threads;
}

UGKDM_HardwareVector CDeviceManager::getHardware()
{
	return hardware_vector;
}
CHardware* CDeviceManager::getHardware(int index)
{
	return hardware_vector[index];
}

bool CDeviceManager::isActive(int index)
{
	return active_vector[index];
}

CHardware * CDeviceManager::NewHW(CHW_HARDWARE_TYPE HWType)
{
	CHardware *HW;

	switch (HWType)
	{
	case CHW_SOUND:		//Output sound through a sounds card
		HW = new UGKAudioHardware();
		break;
	case CHW_GRAPHIC:	//Output video through a graphics cardcard
		HW = new CGraphicCard();
		break;
	case CHW_IN_KEYBOARD:		///< Device Keyboard
		HW = new CKeyboard();
		break;
	case CHW_IN_MOUSE:			///< Device Mouse
		HW = new CMouse();
		break;
	case CHW_IN_JOYSTICK:		///< Device Joystick
		HW = new CJoystick(-1);
		break;
	case CHW_IN_GAMECONTROLLER:	///< Device Game Controller
		HW = new CGameController(-1);
		break;
#ifdef CHW_USE_WIIMOTE
	case CHW_IN_WIIMOTE:		///< Device Wiimote
		HW = new CWiiMote(-1);
		break;
#endif
#ifdef CHW_USE_KINECT
	case CHW_IN_KINECT:			///< Device Kinect
		HW = new CKinect();
		break;
#endif
	case CHW_IN_WEBCAM:			///< Device Web Cam
		HW = new UGKWebCam();
		break;
#ifdef CHW_USE_LEAP
	case CHW_IN_LEAP:			///< Device Leap Motion
		HW = new UseLeap();
		break;
#endif
	case CHW_IN_GLOVE:			///< Device Guante
		// Not yet implemented
		HW = NULL;
		break;
	case CHW_IN_GENERIC:		///< Device Generic
		HW = new CHardware();
		break;
	case CHW_IN_MIC:			///< Device Microphone
		// Not yet implemented
		HW = NULL;
		break;
	case CHW_IN_TOUCHSCREEN:	///< Device Touch Screen. For tablets*/
		// Not yet implemented
		HW = NULL;
		break;
	default:
		HW = NULL;
		break;
	}
	return HW;
}