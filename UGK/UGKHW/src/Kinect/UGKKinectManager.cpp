/**	Kinect Manager class and methods for using a kinect device.
*	Prefix: KNTM_
*	@version: 2011-12
*	@NewVersion Francisco Romero 2014-12 - UGKKinectManager like polling controler using UGKKinect.
**/

#include <UGKKinectManager.h>
#include <conio.h> ///<Used for keyboard events.

/**
* CHW_USE_KINECT definition for UGKKinectManager and UGKKinect version 2014-10 (using OpenNi/NiTE 2.2)
*/
#ifdef CHW_USE_KINECT

	using namespace UGK;

	/**   
	* It defines the types of kinectManager's messages
	*/
	typedef enum { 
		KNTM_UMSG_EMPTY_MSG, //For management purposes only 
		KNTM_INIT_KINECT, 
		KNTM_WAIT_KINECT, 
		KNTM_UPDATE_KINECT, 
		KNTM_CLOSE_KINECT,
		KNTM_UMSG_MAX_TYPE //For management purpouses only 
	} KNTM_UMSG_TYPE;

	/**
	*	@fn void CKinectManager::CKinectManager(void)
	*	Constructor of the class.
	*/
	CKinectManager::CKinectManager(void)
	{
		TypeHW      = CHW_IN_KINECT;			// Define Type Hardware In
		SubTypeHW   = CHW_IN_KINECT;		// Define SubType Kinect
		Status = CHW_HW_ACTIVE;					// Define Active Kinect

		Init();
	}

	/**
	*	@fn void CKinectManager::~CKinectManager(void)
	*	Destructor of the Class.
	*/
	CKinectManager::~CKinectManager(void)
	{
		cleanupExit();
	}


	/**
	*	@fn int CKinect::initKinect()
	*	Start kinect(s).
	*/
	CHW_HW_STATUS CKinectManager::Init(void)
	{
		g_kinect = UGK::CKinect::CKinect();

		g_kinect.Init();
		g_kinect.waitKinect();

		SetDelay (KNTM_KINECT_MIN_UPDATETIME);

		//Check if kinect has been detected
		return CHW_HW_INITIALIZED;

		// Future work:
		//RTDESK_CMsg *pMsg = nRTDESK_CMsg; 
		//pMsg->Propietary = true; 
		//RTDESK_TIME updateTime = ms2Ticks(TIEMPO_REFRESCO); 
		//SendSelfMsg (pMsg, updateTime);
	}

	/**
	*	@fn bool CKinectManager::waitKinect()
	*	Kinect is waiting to person perform wave gesture (hand gesture).
	*   @return True or false indicating success or failure of this operation.
	*/
	bool CKinectManager::wait()
	{
		return (g_kinect.waitKinect());
	}

	/**
	*	@fn CKinectManager::update()
	*	Call kinect(s) for returning new hand(s) position(s), and transform to keyboard events.
	*/
	K_SHIP_MOVE CKinectManager::update(void)
	{
		UGK::K_SHIP_MOVE ksm = UGK::K_SHIP_MOVE::K_STOP_MOVE;

		if (HRTimerManager->GetTimer(0)->IsSounding())
		{
			HRTimerManager->GetTimer(0)->ResetAlarm();

			ksm = g_kinect.updateKinect();
		
			//VK_RIGHT,	//CSIK_PLAYER_MOVE_RIGHT	Player ship is move rightwards
			//VK_LEFT,	//CSIK_PLAYER_MOVE_LEFT		Player ship is move leftwards
			//VK_UP,		//CSIK_PLAYER_SHOOT			Laser fire

			switch (ksm)
			{
			case UGK::K_SHIP_MOVE::K_LEFT_MOVE:
				// pulsar flecha izquierda
				_ungetch(VK_LEFT);
				break;

			case UGK::K_SHIP_MOVE::K_RIGHT_MOVE:
				// pulsar flecha derecha
				_ungetch(VK_RIGHT);
				break;	

			case UGK::K_SHIP_MOVE::K_UP_MOVE:
				// pulsar flecha arriba
				_ungetch(VK_UP);
				break;

			case UGK::K_SHIP_MOVE::k_DOWN_MOVE:
				// pulsar flecha abajo
				_ungetch(VK_DOWN);
				break;	

			//VK_SEPARATER

			default:
				break;
			}
			 
		}
		return ksm;
	}


	/**
	*	@fn void CKinectManager::cleanupExit()
	*	Clean up for shutting down kinect device(s).
	*/
	void CKinectManager::cleanupExit()
	{
		g_kinect.Finish();

	}

	/**   
	* @fn CKinectManager::SetDelay (HRT_Time D)
	* Establishes Kinect(s) delay. This sets the minimun repeating period of a Kinect gesture capture.
	* @param HRT_Time D Frecuency or time in long long format.
	* Set the alarm for D time.
	*/
	void CKinectManager::SetDelay (HRT_Time D)
	{
		HRTimerManager->CreateTimers(0);	///<Every previous timer is released and new one are generated and reset to 0

		HRTimerManager->GetTimer(0)->SetAlarm (D);	///<Copies the action keys list
		HRTimerManager->GetTimer(0)->ResetAlarm();
	}

	/**   
	* @fn CKinectManager::SetDelay (float F)
	* Establishes Kinect(s) delay. This sets the minimun repeating period of a Kinect gesture capture.
	* @param float F Frecuency or time in float format.
	* Set the alarm for F time.
	*/
	void CKinectManager::SetDelay (float F)
	{
		HRTimerManager->CreateTimers(0); ///<Every previous timer is released and new one are generated and reset to 0

		HRTimerManager->GetTimer(0)->SetAlarm (F*HRTimerManager->GetTimer(0)->GetSamplingFreqms());	///<Copies the action keys list
	}


	/// FUTURE WORK:

	//RTDesk virtual Function redefinition
	void CKinectManager::ReceiveMessage(RTDESK_CMsg *pMsg)
	{
		/* ejemplo 1:

		if (RENDER==pMsg->Type) {DrawPicture(); SendSelfMsg(pMsg, RenderSampling);}
		*/

		/* ejemplo 2:

		switch(pMsg->Type) { 
			case TEST_INIT_SERVICE: 
				Time = 500 + rand()%250 //between 500 and 750 ms MsgLP = (MSG_LoginPwd*) 
				GetMsgToFill(TEST_SEND_LOGIN_PASSWORD); 
				MsgLP->Type = TEST_SEND_LOGIN_PASSWORD; 
				MsgLP->Log = (char *) GetName().c_str(); 
				MsgLP->Pwd = "1234"; //Set values to pMsgInitSess and send it 
				SendMsg(MsgLP, &Object[j], Time);

				RTDESK_TIME RenderSampling = ms2Ticks(1000.0/fps); 
				SendSelfMsg(pMsg, RenderSampling);
				break; 
			default: 
				//Log.Write("Error Msg\n"); 
		}
		*/

		/* ejemplo 3:

		switch ( pMsg->MessageType ) { 
			case RTDESK_BOLA_MSG_SIMULATION: 
				Simulation(pMsg->Tiempo); 
				break; 
			case RTDESK_BOLA_MSG_MSG: 
				message(pMsg->vector,pMsg->rad, pMsg->msg, pMsg->param, pMsg->data); 
				break; 
			case RTDESK_BOLA_SUPERBOLA: 
				... 
				pMsg->MessageType = RTDESK_BOLA_SUPERBOLA; 
				pMsg->Tiempo = TIEMPO_BOLA; 
				RTDESK_SendMessage(pMsg, *this, TIEMPO_BOLA);
				break; 
		} 
		*/

		/* ejemplo 4:

		// Proceso de visualización
		g_flyengine->draw_frame(); 
		// Envía un mensaje con el siguiente render 
		RTDESK_SendMessage (pMsg, *this, RenderTime);
		*/

		g_kinect.updateKinect();

		//RTDESK_TIME updateTime = ms2Ticks(TIEMPO_REFRESCO); 
		//SendSelfMsg (pMsg, updateTime);
	
	}

	//class MSG_EmptyMsg: public RTDESK_CMsg{}; 
	//class MSG_SendContent: public RTDESK_CMsg {public: unsigned int SesionId; MSG_ContentType Type;}; 

#endif
