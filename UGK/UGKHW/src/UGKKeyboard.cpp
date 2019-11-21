/** 
*	Class Keyboard

*	Class prefix: CK_

*	@author Ramon Molla
*	@version 2016-02
*/

#include <UGKKeyboard.h>

using namespace UGK;

#ifdef	UGKOS_WINDOWS

//Translation control buttons from the given operating system to the internal reference to the key touched.
//This table is deprecated, the SDL one should be used instead.
char CK_OS_CTRL_INPUTS[CK_KB_MAX_CTROL_INPUTS] = 
{
	//Mouse buttons
	VK_LBUTTON,
	VK_RBUTTON,
	VK_CANCEL,
	VK_MBUTTON,

	//Control keys
	VK_BACK,
	VK_TAB,
	VK_ESCAPE,
	VK_SPACE,
	VK_PRIOR,
	VK_NEXT,
	VK_END,
	VK_HOME,
	VK_LEFT,
	VK_UP,
	VK_RIGHT,
	VK_DOWN,
	VK_SELECT,
	VK_PRINT,
	VK_EXECUTE,
	VK_SNAPSHOT,
	VK_INSERT,
	VK_DELETE,
	VK_HELP,
	VK_SLEEP,

	//Numeric Pad
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
	VK_MULTIPLY,
	VK_ADD,
	VK_SEPARATOR,
	VK_SUBTRACT,
	VK_DECIMAL,
	VK_DIVIDE,
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
	VK_F13,
	VK_F14,
	VK_F15,
	VK_F16,
	VK_F17,
	VK_F18,
	VK_F19,
	VK_F20,
	VK_F21,
	VK_F22,
	VK_F23,
	VK_F24,

	VK_NUMLOCK,
	VK_SCROLL,
	VK_LSHIFT,
	VK_RSHIFT,
	VK_LCONTROL,
	VK_RCONTROL,
	VK_LMENU,
	VK_RMENU,
	VK_BROWSER_BACK,
	VK_BROWSER_FORWARD,
	VK_BROWSER_REFRESH,
	VK_BROWSER_STOP,
	VK_BROWSER_SEARCH,
	VK_BROWSER_FAVORITES,
	VK_BROWSER_HOME,
	
	//Multimedia control
	VK_VOLUME_MUTE,
	VK_VOLUME_DOWN,
	VK_VOLUME_UP,
	VK_MEDIA_NEXT_TRACK,
	VK_MEDIA_PREV_TRACK,
	VK_MEDIA_STOP,
	VK_MEDIA_PLAY_PAUSE,
	VK_LAUNCH_MAIL,
	VK_LAUNCH_MEDIA_SELECT,
	VK_LAUNCH_APP1,
	VK_LAUNCH_APP2,
	
		//Game Pads
	VK_GAMEPAD_A,
	VK_GAMEPAD_B,
	VK_GAMEPAD_X,
	VK_GAMEPAD_Y,
	VK_GAMEPAD_RIGHT_SHOULDER,
	VK_GAMEPAD_LEFT_SHOULDER,
	VK_GAMEPAD_LEFT_TRIGGER,
	VK_GAMEPAD_RIGHT_TRIGGER,
	VK_GAMEPAD_DPAD_UP,
	VK_GAMEPAD_DPAD_DOWN,
	VK_GAMEPAD_DPAD_LEFT,
	VK_GAMEPAD_DPAD_RIGHT,
	VK_GAMEPAD_MENU,
	VK_GAMEPAD_VIEW,
	VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON,
	VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON,
	VK_GAMEPAD_LEFT_THUMBSTICK_UP,
	VK_GAMEPAD_LEFT_THUMBSTICK_DOWN,
	VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT,
	VK_GAMEPAD_LEFT_THUMBSTICK_LEFT,
	VK_GAMEPAD_RIGHT_THUMBSTICK_UP,
	VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN,
	VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT,
	VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT,
};

#elif	defined(UGKOS_LINUX)
//Translation control buttons from the given operating system to the internal reference to the key touched.
char CK_OS_CTRL_INPUTS[CK_KB_MAX_CTROL_INPUTS] =
{
	TO DO Set here the O.S. labels associated to the keyboardinput 
}
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

char CK_SDL_KB_INPUTS[UGK_KB_MAXKEYS] = {
	SDLK_0,
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_4,
	SDLK_5,
	SDLK_6,
	SDLK_7,
	SDLK_8,
	SDLK_9,

	SDLK_a,
	SDLK_AC_BACK,
	SDLK_AC_BOOKMARKS,
	SDLK_AC_FORWARD,
	SDLK_AC_HOME,
	SDLK_AC_REFRESH,
	SDLK_AC_SEARCH,
	SDLK_AC_STOP,
	SDLK_AGAIN,
	SDLK_ALTERASE,
	SDLK_QUOTE,
	SDLK_APPLICATION,
	SDLK_AUDIOMUTE,
	SDLK_AUDIONEXT,
	SDLK_AUDIOPLAY,
	SDLK_AUDIOPREV,
	SDLK_AUDIOSTOP,

	SDLK_b,
	SDLK_BACKSLASH,
	SDLK_BACKSPACE,
	SDLK_BRIGHTNESSDOWN,
	SDLK_BRIGHTNESSUP,

	SDLK_c,
	SDLK_CALCULATOR,
	SDLK_CANCEL,
	SDLK_CAPSLOCK,
	SDLK_CLEAR,
	SDLK_CLEARAGAIN,
	SDLK_COMMA,
	SDLK_COMPUTER,
	SDLK_COPY,
	SDLK_CRSEL,
	SDLK_CURRENCYSUBUNIT,
	SDLK_CURRENCYUNIT,
	SDLK_CUT,

	SDLK_d,
	SDLK_DECIMALSEPARATOR,
	SDLK_DELETE,
	SDLK_DISPLAYSWITCH,
	SDLK_DOWN,

	SDLK_e,
	SDLK_EJECT,
	SDLK_END,
	SDLK_EQUALS,
	SDLK_ESCAPE,
	SDLK_EXECUTE,
	SDLK_EXSEL,

	SDLK_f,
	SDLK_F1,
	SDLK_F10,
	SDLK_F11,
	SDLK_F12,
	SDLK_F13,
	SDLK_F14,
	SDLK_F15,
	SDLK_F16,
	SDLK_F17,
	SDLK_F18,
	SDLK_F19,
	SDLK_F2,
	SDLK_F20,
	SDLK_F21,
	SDLK_F22,
	SDLK_F23,
	SDLK_F24,
	SDLK_F3,
	SDLK_F4,
	SDLK_F5,
	SDLK_F6,
	SDLK_F7,
	SDLK_F8,
	SDLK_F9,
	SDLK_FIND,

	SDLK_g,
	SDLK_BACKQUOTE,

	SDLK_h,
	SDLK_HELP,
	SDLK_HOME,

	SDLK_i,
	SDLK_INSERT,

	SDLK_j,
	SDLK_k,
	SDLK_KBDILLUMDOWN,
	SDLK_KBDILLUMTOGGLE,
	SDLK_KBDILLUMUP,
	SDLK_KP_0,
	SDLK_KP_00,
	SDLK_KP_000,
	SDLK_KP_1,
	SDLK_KP_2,
	SDLK_KP_3,
	SDLK_KP_4,
	SDLK_KP_5,
	SDLK_KP_6,
	SDLK_KP_7,
	SDLK_KP_8,
	SDLK_KP_9,
	SDLK_KP_A,
	SDLK_KP_AMPERSAND,
	SDLK_KP_AT,
	SDLK_KP_B,
	SDLK_KP_BACKSPACE,
	SDLK_KP_BINARY,
	SDLK_KP_C,
	SDLK_KP_CLEAR,
	SDLK_KP_CLEARENTRY,
	SDLK_KP_COLON,
	SDLK_KP_COMMA,
	SDLK_KP_D,
	SDLK_KP_DBLAMPERSAND,
	SDLK_KP_DBLVERTICALBAR,
	SDLK_KP_DECIMAL,
	SDLK_KP_DIVIDE,
	SDLK_KP_E,
	SDLK_KP_ENTER,
	SDLK_KP_EQUALS,
	SDLK_KP_EQUALSAS400,
	SDLK_KP_EXCLAM,
	SDLK_KP_F,
	SDLK_KP_GREATER,
	SDLK_KP_HASH,
	SDLK_KP_HEXADECIMAL,
	SDLK_KP_LEFTBRACE,
	SDLK_KP_LEFTPAREN,
	SDLK_KP_LESS,
	SDLK_KP_MEMADD,
	SDLK_KP_MEMCLEAR,
	SDLK_KP_MEMDIVIDE,
	SDLK_KP_MEMMULTIPLY,
	SDLK_KP_MEMRECALL,
	SDLK_KP_MEMSTORE,
	SDLK_KP_MEMSUBTRACT,
	SDLK_KP_MINUS,
	SDLK_KP_MULTIPLY,
	SDLK_KP_OCTAL,
	SDLK_KP_PERCENT,
	SDLK_KP_PERIOD,
	SDLK_KP_PLUS,
	SDLK_KP_PLUSMINUS,
	SDLK_KP_POWER,
	SDLK_KP_RIGHTBRACE,
	SDLK_KP_RIGHTPAREN,
	SDLK_KP_SPACE,
	SDLK_KP_TAB,
	SDLK_KP_VERTICALBAR,
	SDLK_KP_XOR,

	SDLK_l,
	SDLK_LALT,
	SDLK_LCTRL,
	SDLK_LEFT,
	SDLK_LEFTBRACKET,
	SDLK_LGUI,
	SDLK_LSHIFT,
		
	SDLK_m,
	SDLK_MAIL,
	SDLK_MEDIASELECT,
	SDLK_MENU,
	SDLK_MINUS,
	SDLK_MODE,
	SDLK_MUTE,

	SDLK_n,
	SDLK_NUMLOCKCLEAR,
	SDLK_o,
	SDLK_OPER,
	SDLK_OUT,

	SDLK_p,
	SDLK_PAGEDOWN,
	SDLK_PAGEUP,
	SDLK_PASTE,
	SDLK_PAUSE,
	SDLK_PERIOD,
	SDLK_POWER,
	SDLK_PRINTSCREEN,
	SDLK_PRIOR,

	SDLK_q,
	SDLK_r,
	SDLK_RALT,
	SDLK_RCTRL,
	SDLK_RETURN,
	SDLK_RETURN2,
	SDLK_RGUI,
	SDLK_RIGHT,
	SDLK_RIGHTBRACKET,
	SDLK_RSHIFT,

	SDLK_s,
	SDLK_SCROLLLOCK,
	SDLK_SELECT,
	SDLK_SEMICOLON,
	SDLK_SEPARATOR,
	SDLK_SLASH,
	SDLK_SLEEP,
	SDLK_SPACE,
	SDLK_STOP,
	SDLK_SYSREQ,

	SDLK_t,
	SDLK_TAB,
	SDLK_THOUSANDSSEPARATOR,

	SDLK_u,
	SDLK_UNDO,
	SDLK_UNKNOWN,
	SDLK_UP,

	SDLK_v,
	SDLK_VOLUMEDOWN,
	SDLK_VOLUMEUP,
	SDLK_w,
	SDLK_WWW,

	SDLK_x,
	SDLK_y,
	SDLK_z,

	SDLK_AMPERSAND,
	SDLK_ASTERISK,
	SDLK_AT,
	SDLK_CARET,
	SDLK_COLON,
	SDLK_DOLLAR,
	SDLK_EXCLAIM,
	SDLK_GREATER,
	SDLK_HASH,
	SDLK_LEFTPAREN,
	SDLK_LESS,
	SDLK_PERCENT,
	SDLK_PLUS,
	SDLK_QUESTION,
	SDLK_QUOTEDBL,
	SDLK_RIGHTPAREN,
	SDLK_UNDERSCORE
};

/**   
   * @fn CKeyboard::CKeyboard()
   * Constructor for the keyboard
*/
CKeyboard::CKeyboard()
{
	int i;

	TypeHW      = CHW_IN_KEYBOARD;		// Define Type Hardware
	SubTypeHW   = CHW_IN_KEYBOARD;		// Define SubType Keyboard
	Status		= CHW_HW_ACTIVE;		// Define Active Keyboard
	ActionSize	= 0;
	
	//Initialize translation table from OS input codification to generic internal UGK codification. Deprecated.
	for (i = 0; i < CK_KB_MAX_CTROL_INPUTS;i++) OS2UGK[CK_OS_CTRL_INPUTS[i]] = i;
	//Initialize translation table from SDL input codification to generic internal UGK codification.
	for (i = 0; i < UGK_KB_MAXKEYS; i++) SDL2UGK[CK_SDL_KB_INPUTS[i]] = i;

#ifdef	UGKOS_WINDOWS
	//* VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	//* 0x3A - 0x40 : unassigned
	//* VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)

	for (i = '0'; i <= '9'; i++) OS2UGK[i] = i;
	for (i = 'A'; i <= 'Z'; i++) OS2UGK[i] = i;

#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif

	Init();
}


void CKeyboard::UpdateAction(const CK_ACTION Token, bool On){}	///<Release a new key from the active list of key pressed

/**
* @fn void CKeyboard::Update()
* Executes the actions associated to all active tokens
*/
void CKeyboard::Update()	///<Release a new key from the active list of key pressed
{
	for (CK_ACTIVE_ACTION::iterator it = ActivActions.begin(); it != ActivActions.end(); ++it)
		if (KeyWait(*it))
			UpdateAction(*it, true);	
}

/**   
   * @fn CKeyboard::~CKeyboard()
   * Destruct Keyboard
*/
CKeyboard::~CKeyboard()
{
	ActivActions.clear();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
/**   
   * @fn CKeyboard::Init
   * Init keys
*/
CHW_HW_STATUS CKeyboard::Init()
{
	///Keyboard INITIALIZATION
	ClearTokensKeys();
	HRTimerManager = CHW_NO_TIMER_MNGR;
	SDL_Init(SDL_INIT_VIDEO);
	return CHW_HW_INITIALIZED;
};

/**
* @fn void CKeyboard::ClearTokensKeys()
* Reset tokens and keys lists
*/
void CKeyboard::ClearTokensKeys()
{
	///Keyboard INITIALIZATION
	ActivActions.clear();
	ActionKeys.clear();
};

/**
   * @fn CKeyboard::SetActionKeys(unsigned char *AK, unsigned char Size)
   * Set the translation table that associates the input lexema (pressed key) to the corresponding token
   * It determines which keys the game is sensitive to
   * @Param char AK List of Action Keys to make the keyboard sensitive to
   * @Param char Size Length of the list
*/

void CKeyboard::SetActionKeys	(unsigned char *AK, unsigned char Size)
{
	ActionSize = Size;
	ClearTokensKeys();

	//The order of the key means the name of the token to be released when the key is pressed
	for (unsigned char i = 0; i< Size; i++)
		ActionKeys[AK[i]] = i;	//Copies the action keys list		
}

/// This method is called by the keyboard parser to save the nexus, the nexus contains the key pressed, the associated action and 
/// the period of the key. The character represents the key pressed, really is the same value that key.
/// The method SetNexus make the structure with the action, the key and the period and this structure is saved in the map ActionKeysP
/// that is indexed by the character
void CKeyboard::SetNexus(UGKS_String key, UGKS_String action, int period)
{
	CK_KAP *structure = new CK_KAP { key, action, period };
	ActionKeysP[key] = structure;	
}

/**   
	* @fn CKeyboard::SetDelay(HRT_Time *D)
	* Establishes Keys delays. This sets the minimun repeating period of a key.
    * @param char AK List of Action Keys to make the keyboard sensitive to
    * @param char Size Length of the list
    * Set the list of actions to keys
    * Check the list of sensitive keys
*/
void CKeyboard::SetDelay	(HRT_Time *D)
{
	//Every previous timer is released and new ActionSize are generated and reset to 0
	HRTimerManager->CreateTimers(ActionSize);

	for (unsigned char i = 0; i< ActionSize; i++)
	{
		HRTimerManager->GetTimer(i)->SetAlarm (D[i]);
		HRTimerManager->GetTimer(i)->ResetAlarm();
	}
}

/**   
	* @fn CKeyboard::SetDelay(float *D)
	* Establishes Keys delays. This sets the minimun repeating period of a key.
    * @param char AK List of Action Keys to make the keyboard sensitive to
    * @param char Size Length of the list
    * Set the list of actions to keys
    * Check the list of sensitive keys
*/
void CKeyboard::SetDelay	(float *D)
{
	//Every previous timer is released and new ActionSize are generated and reset to 0
	HRTimerManager->CreateTimers(ActionSize);

	for (unsigned char i = 0; i< ActionSize; i++)
		HRTimerManager->GetTimer(i)->SetAlarm (D[i]*HRTimerManager->GetTimer(i)->GetSamplingFreqms());	//Copies the action keys list
}

void CKeyboard::SetKeyDelay(float *D, char Token)
{
	HRTimerManager->GetTimer(Token)->SetAlarm(D[Token] * HRTimerManager->GetTimer(Token)->GetSamplingFreqms());
}
void CKeyboard::SetKeyDelay(HRT_Time *D, char Token)
{
	HRTimerManager->GetTimer(Token)->SetAlarm (D[Token]);	//Copies the action keys list
	HRTimerManager->GetTimer(Token)->ResetAlarm();
}

/**
   * @fn CKeyboard::KeyWait(const CK_ACTION Token)
   * Wait for the key
   * @Param char Token to determine if it is the time for repeating again the order associated to this token
   * Avoids to set a lot of repetitive touches
   * @return true if the wait has finished and resets the alarm
*/
bool CKeyboard::KeyWait(const CK_ACTION Token)
{
	if (HRTimerManager->GetTimer(Token)->IsSounding())
	{
		HRTimerManager->GetTimer(Token)->ResetAlarm();
		return true;
	}
	else
		return false;
}

///Avoids to set a lot of repetitive touches
///@return true if the wait has finished and resets the alarm
bool CKeyboard::KeyWaitP(const CK_KAP Estruc)
{
	if (HRTimerManager->GetTimer(atoi(UGKS_string2charstr(Estruc.KEY)))->IsSounding())
			{
		HRTimerManager->GetTimer(atoi(UGKS_string2charstr(Estruc.KEY)))->ResetAlarm();
				return true;
			}
			else
				return false;
}

/**
   * @fn CKeyboard::KeyPressed(const CK_ACTION Token)
   * Set the actions associated to a pressed token
   * @Param char Token to include in the list of active tokens
   */

 void  CKeyboard::SetActiveToken	(const CK_ACTION Token)  	///<Set a new key into the active list of key pressed
{
	 for (CK_ACTIVE_ACTION::iterator it=ActivActions.begin(); it != ActivActions.end(); ++it)
		if(*it == Token)	return;

	ActivActions.push_back(Token);	
	HRTimerManager->GetTimer(Token)->StartSounding();
}
 /// Set the actions associated to a pressed token
 void  CKeyboard::SetActiveTokenP(const  CK_KAP Estruc)  	///<Set a new key into the active list of key pressed
{
	for (CK_ACTIVE_ACTION::iterator it = ActivActions.begin(); it != ActivActions.end(); ++it)
	if (*it == atoi(UGKS_string2charstr(Estruc.KEY)))	return;

	ActivActions.push_back(atoi(UGKS_string2charstr(Estruc.KEY)));
	HRTimerManager->GetTimer(atoi(UGKS_string2charstr(Estruc.KEY)))->StartSounding();
}

/**
   * @fn CKeyboard::KeyReleased(const CK_ACTION Token)
   * Set the actions associated to a released token
   * @Param char Token to exclude in the list of active tokens
*/
void CKeyboard::ResetActiveToken (const CK_ACTION Token)	///<Release a new key from the active list of key pressed
{
	ActivActions.remove(Token);
	HRTimerManager->GetTimer(Token)->DisableAlarm();
	UpdateAction(Token, false);
}
