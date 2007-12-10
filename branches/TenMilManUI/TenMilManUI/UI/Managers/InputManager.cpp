#include "InputManager.h"
#include <TenMilManUI/TenUI_Globals.h>

namespace TenUI {

/***********************************/
/*           Singleton  		   */
/***********************************/
	shared_ptr<InputManager> InputManager::inst;
	shared_ptr<InputManager> InputManager::instance(){
		if(!InputManager::inst){
			InputManager::inst = shared_ptr<InputManager>(new InputManager());
		}
		return InputManager::inst;
	}
	
	InputManager::InputManager(){}	
	InputManager::~InputManager(){
		inputs.clear();
	}
	
	bool InputManager::isQuit(){
		if(!inputs.empty())
		{
			//iterates through checking all UserInputs for isQuit()
			for(InputMapType::iterator i = inputs.begin(); i != inputs.end(); ++i)
			{
				if((i->second)->isQuit())
				{
					std::cout << "InputManager.isQuit(): isQuit = TRUE (userInput request)" << std::endl;
					return true;
				}
			}
			
			return false;
		}
		
		std::cout << "InputManager.isQuit(): isQuit = TRUE (no UserInputs)" << std::endl;
		return true;
	}
	
	bool InputManager::update(){
		if(!inputs.empty())	{
			
			//iterates through updating all UI
			for(InputMapType::iterator i = inputs.begin(); i != inputs.end(); ++i){
				(i->second)->update();			
			}
			
			return true;
		}
		return false;
	}
		
	shared_ptr<UserInput> InputManager::getInput(unsigned long uiid){
		InputMapType::iterator it = inputs.find(uiid);
		if(it != inputs.end()){
			return it->second;
		}
		return shared_ptr<UserInput>();
	}
	
	void InputManager::handleInputEvent(const shared_ptr<Event> &evt){
		shared_ptr<PointEvent> pointEvent = dynamic_pointer_cast<PointEvent>(evt);
		if( pointEvent ){
			shared_ptr<UIComponent> curTarget = getTenUI()->getUIComponentsAt(pointEvent->getX(), pointEvent->getY());
						
			// Send In and Out Events
			if( pointEvent->getType() == PointEvent::MOVE_EVENT_TYPE ){
				
				unsigned long prevTargetID = (UID_PointID_UIComp_Map[pointEvent->getUserID()])[pointEvent->getPointID()];
				if( ((prevTargetID == 0) ^ (!curTarget)) 	||
					((curTarget) && (prevTargetID != curTarget->getObjectID())) ){
					
					// Send Out Event
					if(prevTargetID != 0){

						//cout << "Send Out Event" << endl;
						getTenUI()->getUIComponent(prevTargetID)->handleUserInputEvent(
								shared_ptr<PointEvent>(new PointEvent(	PointEvent::OUT_EVENT_TYPE,
																		pointEvent->getUserID(), 
																		pointEvent->getUserInputID(), 
																		pointEvent->getPointID(),
																		pointEvent->getX(),
																		pointEvent->getY(),
																		pointEvent->getPressed()
																     )
								)
						);	
					}
					
					// Send In Event
					if( curTarget && curTarget->getObjectID() != 0 ){

						//cout << "Send In Event" << endl;
						curTarget->handleUserInputEvent(
								shared_ptr<PointEvent>(new PointEvent(	PointEvent::IN_EVENT_TYPE,
																		pointEvent->getUserID(), 
																		pointEvent->getUserInputID(), 
																		pointEvent->getPointID(),
																		pointEvent->getX(),
																		pointEvent->getY(),
																		pointEvent->getPressed()
																     )
								)
						);	
					}
					
					(UID_PointID_UIComp_Map[pointEvent->getUserID()])[pointEvent->getPointID()] = (curTarget)?curTarget->getObjectID():0;
				}
				
			}		
			
			if(curTarget){
				curTarget->handleUserInputEvent(pointEvent);
			}
			
		}else{
			/*shared_ptr<MultiPointEvent> multiEvent = dynamic_pointer_cast<MultiPointEvent>(evt);
			if( multiEvent ){
			}*/
			cout << "TODO: Handle MultiPointEvent" << endl; //TODO Handle MultiPointEvent
		}
	}
	
	void InputManager::registerInput( const shared_ptr<UserInput>& ui){
		if(ui){
			inputs[ui->getUIID()] = ui;
		}
		
		ui->registerAllEventsHandler(&InputManager::handleInputEvent,InputManager::inst);
	}

}
