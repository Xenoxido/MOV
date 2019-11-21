/**	
*	Prefix: 
*	@Author: Juan Cerrón, Cédric Marco
*	@version: 2013-14
**/

#include <UGKLeapGestureTreatment.h>

using namespace UGK;

CGestureTreatment::CGestureTreatment(void)
{
}


CGestureTreatment::~CGestureTreatment(void)
{
}

/**
* Here we implement the actions to carry out when a movement has been detected.
* Different types of gestures can be detected depending on the device used. 
* In this case, Leap Motion.
**/
void CGestureTreatment::GestureTreatment(GR_GESTURE_TYPE GT) {

	std::cout << "Detectado movimiento: " << GT << std::endl;

}