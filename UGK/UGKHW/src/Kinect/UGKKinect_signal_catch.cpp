/**	
*	Methods for using a kinect device using framework OpenNI & midleware NITE 1.3
*	Prefix: KNT_
*	@Author: Jordi Mansanet 
*	@versión 2011-12
*	@NewVersion Francisco Romero 2014-10 - UGK_API conversion and refactoring to NiTE v2.2
**/
#ifdef CHW_USE_KINECT_1.3

#include <IO/Kinect/UGKKinect_signal_catch.h>
#include <stdio.h>
//#include <unistd.h>
#include <signal.h>


XnBool * g_pValueToSet = NULL;

void SignalHandler(int nSignal)
{
	printf("Caught signal: %d\n", nSignal);
	if (NULL != g_pValueToSet) {
		*g_pValueToSet = true;
	}
}

void CatchSignals(XnBool* bSignalWasCaught)
{
	g_pValueToSet = bSignalWasCaught;

	struct sigaction act;

	memset( &act, 0, sizeof( act ) );
	act.sa_handler = &SignalHandler;
	act.sa_flags = 0;
	sigaction( SIGINT, &act, NULL );
	sigaction( SIGTERM, &act, NULL );
	sigaction( SIGKILL, &act, NULL );
}

#endif
