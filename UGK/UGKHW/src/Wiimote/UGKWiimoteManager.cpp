/**	UGKWiimoteManager.cpp

*	@author Ramon Molla, Imanol Fraile
*	@version 2015-05
*/

//#include "Copyright.h"
#include <cstdio>
#include <Wiimote\UGKWiimoteManager.h>
#include <process.h> // Header File For _beginthread, _endthread 
#include <UGKString.h>
#include <iostream>

#define UGKWM_WII_USE

using namespace UGK;

UGKS_String CWM_Msgs[CWM_MAX_MSG] =
{
	"No Wiimotes Found.",
	"Failed to connect to any wiimote.\n"
};

/**
*	\fn HandleWiimotesActivity()
*	\brief Polls wiimote activity and manages it
*	\param[in] WiimoteMng: The manager that holds the wiimotes
*/
void HandleWiimotesActivity(CWiimoteManager *WiimoteMng) {

	#ifdef UGKWM_WII_USE

	while(1) {
		while (wiiuse_poll(WiimoteMng->WiimoteHW, WiimoteMng->WiimotesAmount)) {
			for (int i = 0; i < WiimoteMng->WiimotesAmount; ++i) {
				switch (WiimoteMng->WiimoteHW[i]->event) {
					case POLLING_EVENT:
						/// Generic event
						WiimoteMng->SetCurrentWiimote(i);
						WiimoteMng->HandleEvent();
						break;

					case POLLING_STATUS:
						/// State event
						WiimoteMng->SetCurrentWiimote(i);
						WiimoteMng->HandleCtrlStatus();
						break;

					case POLLING_DISCONNECT:
					case POLLING_UNEXPECTED_DISCONNECT:
						/// Unexpected disconnection
						WiimoteMng->SetCurrentWiimote(i);
						WiimoteMng->HandleDisconnect();
						break;

					default:
						break;
				}
			}
		}
	}
	#endif
}

/**
*	\fn CWiimoteManager::Init()
*	\brief Starts the use of WiimotesAmount wiimotes
*	\param[in] WiimotesAmount: How many wiimotes to use 
*/
void CWiimoteManager::Init(int WiimotesAmount) {
	int i;

	if (0 > WiimotesAmount) WiimotesAmount = 0;
	if (UGKWMM_MAX_WIIMOTES <= WiimotesAmount) WiimotesAmount = UGKWMM_MAX_WIIMOTES-1;

	CWiimoteManager WmMng = CWiimoteManager(WiimotesAmount);

	/// Initialize the UGKWiimotes and WiimoteHW arrays
	for (i = 0; i < WiimotesAmount; i++) {
		UGKWiiMotes[i] = CWiiMote(i);
		WiimoteHW[i] = UGKWiiMotes[i].WiimoteHW;
	}

	/// Find Wiimotes that are in discovery mode (buttons 1+2 pressed)
	WiimotesFound = Find(WiimotesAmount);
	if (!WiimotesFound) {
		std::cout << CWM_Msgs[CWM_NO_WIIMOTES_FOUND].c_str();
		return;
	}

	/// Connect to the Wiimotes found
	WiimotesConnected = Connect(WiimotesAmount);
	if (WiimotesConnected)
		printf("WiimotesConnected to %i Wiimotes (of %i WiimotesFound).\n", WiimotesConnected, WiimotesFound);
	else {
		std::cout << CWM_Msgs[CWM_WIIMOTES_CONNECT_FAILED].c_str();
		return;
	}

	/// Turn ON the corresponding led of each Wiimote and do a small rumble
	for (i = 0; i < WiimotesAmount; i++) {
		/// Turn ON the wiimote led 'i' of the Wiimote 'i'
		UGKWiiMotes[i].SetLed(i+1);
		
		/// Turn ON the rumble of the Wiimote 'i'
		UGKWiiMotes[i].StartRumble();
		
		/// Turn OFF the rumble of the Wiimote 'i'
		UGKWiiMotes[i].StopRumble();
	}

	_beginthread((void (__cdecl *)(void *))HandleWiimotesActivity,sizeof(CWiimoteManager),this);
	return;
}

/**
*	\fn CWiimoteManager::~CWiimoteManager()
*	\brief Destroys the data structure of the wiimotes and disconnects them
*/
CWiimoteManager::~CWiimoteManager() {
	/// Disconnect the Wiimotes
	Cleanup(WiimotesAmount);
}

/**
*	\fn CWiimoteManager::HandleEvent()
*	\brief Activates or deactivates the motion sensing of the wiimote
*		   by pressing the 'PLUS' or 'MINUS' buttons
*/
void CWiimoteManager::HandleEvent() {
	/// Check if button 'PLUS' has been pressed
	if (UGKWiiMotes[CurrentWiimote].IsButtonPlusJustPressed())
		/// Turn ON the motion sensing of the current Wiimote
		UGKWiiMotes[CurrentWiimote].StartMotionSensing();
		
	/// Check if button 'MINUS' has been pressed
	if (UGKWiiMotes[CurrentWiimote].IsButtonMinusJustPressed())
		/// Turn OFF the motion sensing of the current Wiimote
		UGKWiiMotes[CurrentWiimote].StopMotionSensing();
}

/**
*	\fn CWiimoteManager::HandleRead()
*	\brief Shows the information passed to the user
*	\param[in] data: Information to show out to the user
*	\param[in] len:  Amount of information passed to be output
*/
void CWiimoteManager::HandleRead(byte* data, unsigned short len) {
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", UGKWiiMotes[CurrentWiimote].GetUid());
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i%16))
			printf("\n");
		printf("%x ", data[i]);
	}
	printf("\n\n");
}

/**
*	\fn CWiimoteManager::HandleCtrlStatus()
*	\brief Shows the current wiimote status to the user
*/
void CWiimoteManager::HandleCtrlStatus() {

	#ifdef UGKWM_WII_USE

	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", UGKWiiMotes[CurrentWiimote].GetUid());
	printf("Speaker:         %i\n",			 UGKWiiMotes[CurrentWiimote].IsUsingSpeaker());
	printf("IR:              %i\n",			 UGKWiiMotes[CurrentWiimote].IsUsingIR());
	printf("Leds:            %i %i %i %i\n", UGKWiiMotes[CurrentWiimote].IsLedSet(1),
											 UGKWiiMotes[CurrentWiimote].IsLedSet(2),
											 UGKWiiMotes[CurrentWiimote].IsLedSet(3),
											 UGKWiiMotes[CurrentWiimote].IsLedSet(4));
	printf("Battery:         %f %%\n",		 UGKWiiMotes[CurrentWiimote].WiimoteHW->battery_level);

	#endif
}

/**
*	\fn CWiimoteManager::HandleDisconnect()
*	\brief Shows the current wiimote id to the user that has
		   been unexpectedly disconnected from the system
*/
void CWiimoteManager::HandleDisconnect() {
	printf("\n\n--- Wiimote unexpectedlly disconnected [wiimote id %i] ---\n", UGKWiiMotes[CurrentWiimote].GetUid());
}

/**
*	\fn CWiimoteManager::Vibrate()
*	\brief Let the current wiimote to perform a vibration
*/
void CWiimoteManager::Vibrate() {
	/// Turn ON the rumble of the Wiimote passed as a parameter
	UGKWiiMotes[CurrentWiimote].StartRumble();
	
	/// Turn OFF the rumble of the Wiimote passed as a parameter
	UGKWiiMotes[CurrentWiimote].StopRumble();

	return;
}
