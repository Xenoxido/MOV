/**	
*	Prefix: 
*	@Author: Juan Cerrón, Cédric Marco
*	@version: 2013-14
**/

#include <UGKLeap.h>

using namespace UGK;

UseLeap::UseLeap()		///<Constructor of the class
{
	TypeHW = CHW_IN_LEAP;		// Define Type Hardware
	Status = CHW_HW_ACTIVE;					// Define Active Keyboard

}

CHW_HW_STATUS UseLeap::findHardware()	/// Find Leap
{

	if (-1 == UseLeap::Init()){
		return CHW_HW_NOT_FOUND;
	}
	else{
		return CHW_HW_INITIALIZED;
	}
}


	/**
	 * It initializes the controller used by the Leap motion device in
	 * case it is connected. 
	 * -1 is returned with no device detected.
	 */
CHW_HW_STATUS UseLeap::Init() {
	// Have the sample listener receive events from the controller
	
	// Check if there is atleast one leap motion device connected

	// IT DOESN'T WORK BECAUSE OF THE LEAP API FUNCTIONS 
	/*DeviceList device = controller.devices();

	if (device.isEmpty())
		return -1;
	else{
		controller.addListener(detectorMovimientos);
		return 1;
	}*/

	controller.addListener(detectorMovimientos);
	return CHW_HW_INITIALIZED;
}

void UseLeap::Finish() {
	// Remove the sample listener when done
	controller.removeListener(detectorMovimientos);
	//std::cout << "Exited" << std::endl;
}

