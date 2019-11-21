/**	
*	Prefix: 
*	@Author: Juan Cerrón, Cédric Marco
*	@version: 2013-14
**/

#include <iostream>
#include <UGKLeapGestureRecognizer.h>

using namespace UGK;

void CGestureRecognizer::onInit(const Controller& controller) {
  //Note: not dispatched when running in a debugger.
  std::cout << "Initialized" << std::endl;
}

void CGestureRecognizer::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_SWIPE);

}

void CGestureRecognizer::onExit(const Controller& controller) {
  //Note: not dispatched when running in a debugger.
  std::cout << "Exited" << std::endl;
}

void CGestureRecognizer::onDisconnect(const Controller& controller) {
  //Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void CGestureRecognizer::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  // Get gestures
  const GestureList gestures = frame.gestures();

  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];

    switch (gesture.type()) {
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        UGKS_String clockwiseness;

        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
          clockwiseness = "clockwise";
        } else {
          clockwiseness = "counterclockwise";
        }

        // Calculate angle swept since last frame
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }

		/* Utilizamos el movimiento circular de un dedo para saber el tipo de disparo.
		Si es en el sentido de las agujas del reloj, será un disparo normal, y en el 
		sentido contrario a las agujas del reloj, se tratará de un lanzamiento de bomba*/

		if (clockwiseness == "clockwise"){ 
			//std::cout << "DISPARA" << std::endl;
			GestureTreatment(GR_QUICK_SHOOT_MOVE);
		}
		else if (clockwiseness == "counterclockwise"){ 
			//std::cout << "DISPARA BOMBA" << std::endl;
			GestureTreatment(GR_SLOW_SHOOT_MOVE);
		}

        break;
      }
      case Gesture::TYPE_SWIPE:
      {
			SwipeGesture swipe = gesture;
			Leap::Vector direcciones;

			if (swipe.state() != Gesture::STATE_START) {
				
				SwipeGesture previousUpdate = SwipeGesture(controller.frame(1).gesture(gesture.id()));
				direcciones = (swipe.direction() - previousUpdate.direction());
				
			}

			/* Comprobamos la dirección del movimiento, tendremos en cuenta el gesto si su dirección
			en cualquiera de los ejes es mayor que 0.85 */

			// Comprobamos el desplazamiento horizontal
			if (std::abs(swipe.direction().x) > 0.85){ 
				if (swipe.direction().x < 0){
					//std::cout << "IZQUIERDA" << std::endl;
					GestureTreatment(GR_LEFT_MOVE);
				}
				else{
					//std::cout << "DERECHA" << std::endl;
					GestureTreatment(GR_RIGHT_MOVE);
				}
			}
			// Comprobamos el desplazamiento vertical
			else if (std::abs(swipe.direction().y) > 0.85){ 
				if (swipe.direction().y < 0){
					//std::cout << "ABAJO" << std::endl;
					GestureTreatment(GR_BOTTOM_MOVE);
				}
				else{
					//std::cout << "ARRIBA" << std::endl;
					GestureTreatment(GR_TOP_MOVE);
				}
			}
			// Comprobamos el desplazamiento en profundidad
			else if (std::abs(swipe.direction().z) > 0.85){ 
				if (swipe.direction().z < 0){
					//std::cout << "ADELANTE" << std::endl;
					GestureTreatment(GR_FORWARD_MOVE);
				}
				else{
					//std::cout << "ATRAS" << std::endl;
					GestureTreatment(GR_BACKWARD_MOVE);
				}
			}
		

        break;
      }
   
      default:
        //std::cout << "Unknown gesture type." << std::endl;
        break;
    }
  }

  if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    //std::cout << std::endl;
  }

  m_lastFrame = frame;
}

void CGestureRecognizer::onFocusGained(const Controller& controller) {
  m_lastFrame = controller.frame();
}

void CGestureRecognizer::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}
