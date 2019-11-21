/**	Implementation of the class UGKkinect. Methods for using a kinect device.
*
*	Prefix: KNT_
*
*	@file	 UGKKinect.h
*	@brief	Class for using a kinect device.
*	@Author: Jordi Mansanet versión
*	@version: 2011-12
*	@NewVersion Francisco Romero 2014-10 - UGK_API conversion and update to NiTE v2.2
*   @References:
*		NiTE Writing an application http://www.openni.ru/resources/index.html
*		OpenNI/NiTE 2 Migration Guide http://com.occipital.openni.s3.amazonaws.com/OpenNI_Migration_Guide_1_to_2.pdf
**/

#include <Kinect/UGKKinect.h> 

/**
* CHW_USE_KINECT definition for UGKKinect version 2014-10 (using OpenNi/NiTE 2.2)
*/
#ifdef CHW_USE_KINECT


///We use the UGK namespace to make the code cleaner
using namespace UGK;

#include <stdio.h>

/**   
* It defines the types of kinect's messages
* @param enum KNT_Msgs which lists the message allowed the kinect
*/
UGKS_String KNT_Msgs[KNT_ERROR_MAX_MSG] =
{
	"NiTE initialization failed\n",
	"Couldn't create user tracker\n",
	"\nWave or click to start tracking your hand...\n",
	"Get next frame failed\n",
	"LEFT !!",
	"CENTER !!",
	"RIGHT !!",
	"UP !!",		
	"DOWN !!",	
	"FORWARD !!",	
	"BACKWARD !!",
	"WARNING: wrong value on slider"
};


/**
*	@fn void CKinect::CKinect(void)
*	Constructor of the class.
*/
CKinect::CKinect(void)
{
	TypeHW      = CHW_IN_KINECT;		// Define Type Hardware In
	SubTypeHW   = CHW_IN_KINECT;		// Define SubType Kinect
	Status = CHW_HW_ACTIVE;					// Define Active Kinect (Implicitly it needs to be alive in order to be active)

	direccion_horizontal = KNT_Msgs[KNT_CENTER];
	direccion_vertical =  KNT_Msgs[KNT_CENTER];
	direccion_profundidad = KNT_Msgs[KNT_CENTER];
	sensibility = KNT_SENSIBILITY_DEFAULT; ///<Sensibility range LEFT-CENTER-RIGTH, UP-CENTER-DOWN and FORWARD-CENTER-BACKWARD
	g_dir=K_STOP_MOVE;
}

/**
*   @fn void CKinect::~CKinect(void)
*	Destructor of the Class.
*/
CKinect::~CKinect(void)
{
}

/**
*	@fn int CKinect::Init()
*	Start kinect.
*/
CHW_HW_STATUS CKinect::Init()
{
	niteRc = nite::NiTE::initialize();
	if (niteRc != nite::STATUS_OK)
	{
		printf(UGKS_string2charstr(KNT_Msgs[KNT_BAD_INIT]));
		return CHW_HW_NOT_FOUND;
	}

	niteRc = handTracker.create();
	if (niteRc != nite::STATUS_OK)
	{
		printf(UGKS_string2charstr(KNT_Msgs[KNT_BAD_TRACKER]));
		return CHW_HW_NOT_FOUND;
	}
	return CHW_HW_INITIALIZED;
}

/**
*	@fn CHW_HW_STATUS CKinect::findHardware()
*	Find kinect.
*/

CHW_HW_STATUS CKinect::findHardware()
{
	CHW_HW_STATUS S = Init();

	if(CHW_HW_INITIALIZED == S)
		return CHW_HW_NOT_FOUND;
	else
		return CHW_HW_NOT_FOUND;	
}

/**
*	@fn bool CKinect::waitKinect()
*	Kinect is waiting to person perform wave gesture (hand gesture).
*   @return True or false indicating success or failure of this operation.
*/
bool CKinect::waitKinect()
{
	
	niteRc = handTracker.startGestureDetection(nite::GESTURE_WAVE);
	niteRc = handTracker.startGestureDetection(nite::GESTURE_CLICK);
	printf(UGKS_string2charstr(KNT_Msgs[KNT_WAVE_OR_CLICK]));
	return (niteRc == nite::STATUS_OK);
}


/**
*	@fn K_SHIP_MOVE CKinect::updateKinect()
*	Kinect returns new hand position.
*   @return K_SHIP_MOVE of the last hand-gesture frame read.
*/
K_SHIP_MOVE CKinect::updateKinect()
{
	niteRc = handTracker.readFrame(&handTrackerFrame);
	if (niteRc != nite::STATUS_OK)
	{
		printf(UGKS_string2charstr(KNT_Msgs[KNT_BAD_FRAME]));
		//continue;
		g_dir=K_STOP_MOVE;
	}
	else
	{
		const nite::Array<nite::GestureData>& gestures = handTrackerFrame.getGestures();
		for (int i = 0; i < gestures.getSize(); ++i)
		{
			if (gestures[i].isComplete())
			{
				nite::HandId newId;
				handTracker.startHandTracking(gestures[i].getCurrentPosition(), &newId);
			}
		}

		const nite::Array<nite::HandData>& hands = handTrackerFrame.getHands();
		for (int i = 0; i < hands.getSize(); ++i)
		{
			const nite::HandData& hand = hands[i];
			if (hand.isTracking())
			{
				// Eje X
				if (hand.getPosition().x <= -sensibility)
				{
					direccion_horizontal = KNT_Msgs[KNT_LEFT];
					g_dir=K_LEFT_MOVE;
				}
				else if (hand.getPosition().x > -sensibility && hand.getPosition().x <= sensibility)
				{
					
					direccion_horizontal = KNT_Msgs[KNT_CENTER];
					g_dir=K_STOP_MOVE;
				}
				else if (hand.getPosition().x > sensibility)
				{
					
					direccion_horizontal = KNT_Msgs[KNT_RIGHT];
					g_dir=K_RIGHT_MOVE;
				}
				else 
				{
					direccion_horizontal = KNT_Msgs[KNT_WRONG_VALUE_SLIDER];
				}
				
				// Eje Y
				if (hand.getPosition().y <= -sensibility)
				{
					direccion_vertical = KNT_Msgs[kNT_DOWN];
					//g_dir=k_DOWN_MOVE;
				}
				else if (hand.getPosition().y > -sensibility && hand.getPosition().y <= sensibility)
				{
					
					direccion_vertical = KNT_Msgs[KNT_CENTER];
					//g_dir=K_STOP_MOVE;
				}
				else if (hand.getPosition().y > sensibility)
				{
					
					direccion_vertical = KNT_Msgs[KNT_UP];
					//g_dir=K_UP_MOVE;
				}
				else
				{
					direccion_vertical = KNT_Msgs[KNT_WRONG_VALUE_SLIDER];
				}

				// Eje Z
				if (hand.getPosition().z <= -sensibility)
				{
					direccion_profundidad = KNT_Msgs[KNT_FORWARD];
					//g_dir=K_FORWARD_MOVE;
				}
				else if (hand.getPosition().z > -sensibility && hand.getPosition().y <= sensibility)
				{
					
					direccion_profundidad = KNT_Msgs[KNT_CENTER];
					//g_dir=K_STOP_MOVE;
				}
				else if (hand.getPosition().z > sensibility)
				{
					
					direccion_profundidad = KNT_Msgs[KNT_BACKWARD];
					//g_dir=K_BACKWARD_MOVE;
				}
				else
				{
					direccion_profundidad = KNT_Msgs[KNT_WRONG_VALUE_SLIDER];
				}

				printf("%s - %s - %s\n",direccion_horizontal, direccion_vertical, direccion_profundidad);

				//printf("%d. (%5.2f, %5.2f, %5.2f)\n", hand.getId(), hand.getPosition().x, hand.getPosition().y, hand.getPosition().z);
			}
		}
	}
	return g_dir;
}


/**
*	@fn void CKinect::Finish()
*	Clean up for shutting down kinect.
*/
void CKinect::Finish()
{
	nite::NiTE::shutdown();
}

UGKS_String		CKinect::getProperties()			///<Get kinect properties
{
	return "";
}

#elif defined(CHW_USE_KINECT_1_3)

	///We use the UGK namespace to make the code cleaner
	using namespace UGK;

	/**   
	* It defines the types of kinect's messages
	* @param enum KNT_Msgs which lists the message allowed the kinect
	*/
	CString KNT_Msgs[KNT_ERROR_MAX_MSG]= 
	{
		"WARNING: nItem = -1",
		"Slider: Bad direction for selection: %s\n",
		"WARNING: wrong direction",
		"LEFT !!",
		"CENTER !!",
		"RIGHT !!",
		"WARNING: wrong value on slider",
		"Init From Xml",
		"Init From Xml File",
		"Find depth generator",
		"Couldn't initialize the Session Manager: %s\n",
		"Please perform wave gesture to start session\n",
		"Hit any key to exit\n"
	};

	// Global variables
	XnVSessionManager* g_pSessionManager = NULL;
	XnVFlowRouter* g_pMainFlowRouter;
	XnVSelectableSlider1D* g_pMainSlider;
	XnBool g_bActive = false;
	XnBool g_bIsInput = false;
	XnBool g_bInSession = false;
	XnFloat g_fValue = 0.5f;
	xn::Context g_Context;
	xn::ScriptNode g_ScriptNode;
	xn::DepthGenerator g_DepthGenerator;
	XnBool g_bQuit = false;
	bool g_session_started = false;
	bool g_init_kinect = false;

	K_SHIP_MOVE g_dir = K_STOP_MOVE; ///<Posicion por defecto del Kinect

	/**   
	* @fn MainSlider_OnSelect
	* Callback Kinect directory
	* @param XnInt32 nItem input variable to the function
	* @param dir XnVDirection input variable of the direction
	* @param cxt void input variable representing the kinect
	* It checks if there nItem and direction is upward and onward
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnSelect(XnInt32 nItem, XnVDirection dir, void* cxt)
	{
		if (nItem == -1) 
		{
			printf(KNT_Msgs[KNT_BAD_ITEM]);
		}
		else if (dir == DIRECTION_UP || dir == DIRECTION_FORWARD)
		{
			printf(KNT_Msgs[KNT_SLIDER_BAD_DIR], XnVDirectionAsString(dir));
		}
		else
		{
			printf(KNT_Msgs[KNT_WRONG_DIR]);
		}
	}

	/**   
	* @fn MainSlider_OnValueChange
	* Call Kinect movements
	* @ Param XnFloat fValue input variable for the movement
	* @ Param cxt void input variable representing the kinect
	* FValue between ranges is checked to determine the direction of movement left, right or center
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnValueChange(XnFloat fValue, void* cxt)
	{
		CString Aux;

		g_bActive = true;
		g_bIsInput = true;
		g_fValue = fValue;
	
		if (fValue >= 0 && fValue <= 0.333)
		{
			Aux = KNT_Msgs[KNT_LEFT];
			g_dir = K_LEFT_MOVE;
		}
		else if (fValue > 0.333 && fValue <= 0.666)
		{
			Aux = KNT_Msgs[KNT_CENTER];
			g_dir = K_STOP_MOVE;
		}
		else if (fValue > 0.666 && fValue <= 1.0)
		{
			Aux =  KNT_Msgs[RIGHT];
			g_dir = K_RIGHT_MOVE;
		}
		else
		{
			Aux = KNT_Msgs[KNT_WRONG_VALUE_SLIDER];
		}
		Aux += "\t\t";
		cout << Aux << fValue << "\n";
	}

	/**   
	* @fn MainSlider_OnActivate
	* Activity Recognition and Kinect
	* @param cxt void input variable representing the kinect
	* Enable status Kinect
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnActivate(void* cxt)
	{
		g_session_started = true;
		g_bActive = true;
		g_bIsInput = false;
	}

	/**   
	* @fn MainSlider_OnDeactivate
	* No Recognition and deactivated the Kinect
	* @param cxt void input variable representing the kinect
	* Turns off the state of Kinect
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnDeactivate(void* cxt)
	{
		g_bActive = false;
		g_bIsInput = false;
	}
	/**   
	* @fn MainSlider_OnPrimaryCreate
	* Create entry of Kinect
	* @param cxt void input variable representing the kinect
	* Enable input Kinect
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnPrimaryCreate(const XnVHandPointContext* hand, const XnPoint3D& ptFocus, void* cxt)
	{
		g_bIsInput = true;
	}
	/**   
	* @fn MainSlider_OnPrimaryDestroy
	* Destroy the entrance of Kinect
	* @param cxt void input variable representing the kinect
	* Allows entry Kinect destroy
	*/
	void XN_CALLBACK_TYPE UGKKinect::MainSlider_OnPrimaryDestroy(XnUInt32 nID, void* cxt)
	{
		g_bIsInput = false;
	}

	/**   
	* @fn SessionStart
	* Start a session for the kinect
	* @param void UserCxt input variable representing the user's kinect
	* Starts a user session for Kinect
	*/
	void XN_CALLBACK_TYPE UGKKinect::SessionStart(const XnPoint3D& pFocus, void* UserCxt)
	{ 
		g_bInSession = true;
		g_pMainFlowRouter->SetActive(g_pMainSlider);
	}

	/**   
	* @fnSessionEnd
	* Close the session for the kinect
	* @param void UserCxt input variable representing the user's kinect
	* Allows user to close the session for Kinect
	*/
	void XN_CALLBACK_TYPE UGKKinect::SessionEnd(void* UserCxt)
	{
		g_bInSession = false;
		g_pMainFlowRouter->SetActive(NULL);
	}

	/**   
	* @fn fileExists
	* There Archives
	* @param char fn represents the names of the files
	* Lets you know if the library file or returning the existence kinect
	*/
	XnBool UGKKinect::fileExists(const char *fn)
	{
		XnBool exists;
		xnOSDoesFileExist(fn, &exists);
		return exists;
	}


	/**   
	* @fn Init
	* Start Kinect
	* This is where you start the kinect and is checked for connection of the same
	* If you activate the state variables and unicia session for Kinect
	* Starts motion capture (flow of movements).
	* It is finished start the kinect once you register a movement with the same
	*/
	CHW_HW_STATUS UGKKinect::Init()
	{
		XnStatus rc = XN_STATUS_OK;
		xn::EnumerationErrors errors;

		rc = g_Context.InitFromXmlFile(SAMPLE_XML_FILE, g_ScriptNode, &errors);
		CHECK_ERRORS(rc, errors, KNT_Msgs[KNT_INIT_FROM_XML_FILE]);
		CHECK_RC(rc, KNT_Msgs[KNT_INIT_FROM_XML]);

		rc = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
		CHECK_RC(rc, KNT_Msgs[KNT_FIND_DEPTH_GEN]);

		// Create and initialize point tracker
		g_pSessionManager = new XnVSessionManager;
		rc = g_pSessionManager->Initialize(&g_Context, "Wave", "RaiseHand");
		if (rc != XN_STATUS_OK)
		{
			printf(KNT_Msgs[KNT_COULD_NOT_INIT_SESSION], xnGetStatusString(rc));
			delete g_pSessionManager;
			return CHW_HW_NOT_INITIALIZED;
		}

		g_pSessionManager->RegisterSession(NULL, &SessionStart, &SessionEnd);

		// Start catching signals for quit indications
		CatchSignals(&g_bQuit);

		// Create and initialize the main slider
		g_pMainSlider = new XnVSelectableSlider1D(3);
		g_pMainSlider->RegisterItemSelect(NULL, &MainSlider_OnSelect);
		g_pMainSlider->RegisterActivate(NULL, &MainSlider_OnActivate);
		g_pMainSlider->RegisterDeactivate(NULL, &MainSlider_OnDeactivate);
		g_pMainSlider->RegisterPrimaryPointCreate(NULL, &MainSlider_OnPrimaryCreate);
		g_pMainSlider->RegisterPrimaryPointDestroy(NULL, &MainSlider_OnPrimaryDestroy);
		g_pMainSlider->RegisterValueChange(NULL, &MainSlider_OnValueChange);
		g_pMainSlider->SetValueChangeOnOffAxis(true);

		// Creat the flow manager
		g_pMainFlowRouter = new XnVFlowRouter;

		// Connect flow manager to the point tracker
		g_pSessionManager->AddListener(g_pMainFlowRouter);

		g_Context.StartGeneratingAll();

		g_init_kinect = true;

		printf(KNT_Msgs[KNT_WAVE_GESTURE]);
		printf(KNT_Msgs[KNT_HIT_ANY_2_EXIT]); 

		return CHW_HW_INITIALIZED;
	}
	/**
	*	@fn bool CKinect::findHardware()
	*	Find kinect.
	*/

	bool CKinect::findHardware(){

		CHW_HW_STATUS x = CKinect::Init()

		if(x){
			return false;
		}else{	
			return true;
		}
	}

	/**   
	* @fn waitKinect
	* Wait Kinect
	* This function defines the standby state kinect
	* While not made any motion is put on hold
	*/
	bool UGKKinect::waitKinect()
	{
		if (g_init_kinect == true)
		{
			// Read next available data
			g_Context.WaitOneUpdateAll(g_DepthGenerator);

			// Process the data
			g_pSessionManager->Update(&g_Context);	
		}	
		return g_session_started;
	}

	/**   
	* @fn updateKinect
	* update de movements of Kinect
	*/
	K_SHIP_MOVE UGKKinect::updateKinect()
	{
		if (g_session_started == true)
		{
			g_init_kinect = false;

			// Read next available data
			g_Context.WaitOneUpdateAll(g_DepthGenerator);

			// Process the data
			g_pSessionManager->Update(&g_Context);
		}
	
		return g_dir;
	}

	/**   
	* @fn Finish
	* Exit Kinect
	* Function for when you finish using the kinect
	* Closes the session user deletes Kinect flow movements
	*/

	void UGKKinect::Finish()
	{
		if (NULL != g_pSessionManager) {
			delete g_pSessionManager;
			g_pSessionManager = NULL;
		}

		delete g_pMainFlowRouter;
		delete g_pMainSlider;

	}

#endif
