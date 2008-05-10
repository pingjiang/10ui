#include "InputManager.h"
#include <TenMilManUI/TenUI_Globals.h>

namespace TenUI {

/***********************************/
/*           Singleton  		   */
/***********************************/
	sp<InputManager> InputManager::inst;
	sp<InputManager> InputManager::instance(){
		if(!InputManager::inst){
			InputManager::inst = sp<InputManager>(new InputManager());
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
		
	sp<UserInput> InputManager::getInput(unsigned long uiid){
		InputMapType::iterator it = inputs.find(uiid);
		if(it != inputs.end()){
			return it->second;
		}
		return sp<UserInput>();
	}
	
	sp< vector< sp<PointEvent> > > InputManager::handlePointEvent(const sp<PointEvent> &pointEvent){
		sp< vector< sp<PointEvent> > > pointEvents(new vector< sp<PointEvent> >());
		sp<UIComponent> curTarget = getTenUI()->getUIComponentsAt(pointEvent->getX(), pointEvent->getY());

		sp<UserInput> userInput = getInput(pointEvent->getUserInputID());

		// Send In and Out Events
		if( pointEvent->getType() == PointEvent::MOVE_EVENT_TYPE ){
			
			unordered_map< unsigned long, unsigned long >::iterator testPrevit = (UID_PointID_UIComp_Map[pointEvent->getUserID()]).find(pointEvent->getPointID());
						
			unsigned long prevTargetID = (testPrevit != (UID_PointID_UIComp_Map[pointEvent->getUserID()]).end())?testPrevit->second:0;
			if( ((prevTargetID == 0) ^ (!curTarget)) 	||
				((curTarget) && (prevTargetID != curTarget->getObjectID())) ){
				
				// Send Out Event
				if(prevTargetID != 0){					
					if( getTenUI()->getUIComponent(prevTargetID) ){
						pointEvents->push_back(
								sp<PointEvent>(
										new PointEvent(	PointEvent::OUT_EVENT_TYPE,
														pointEvent->getUserID(), 
														pointEvent->getUserInputID(), 
														pointEvent->getPointID(),
														pointEvent->getX(),
														pointEvent->getY(),
														pointEvent->getPressed(),
														getTenUI()->getUIComponent(prevTargetID)
										)
								)
						);
					}

				}
				
				// Send In Event
				if( curTarget && curTarget->getObjectID() != 0 && 
					curTarget->getOwnerUserID() == 0 ){
					pointEvents->push_back(
							sp<PointEvent>(
									new PointEvent(	PointEvent::IN_EVENT_TYPE,
													pointEvent->getUserID(), 
													pointEvent->getUserInputID(), 
													pointEvent->getPointID(),
													pointEvent->getX(),
													pointEvent->getY(),
													pointEvent->getPressed(),
													curTarget
									)
							)
					);
				}
				
				(UID_PointID_UIComp_Map[pointEvent->getUserID()])[pointEvent->getPointID()] = (curTarget)?curTarget->getObjectID():0;
				
			}
			
			
		}else if(pointEvent->getType() == PointEvent::UP_EVENT_TYPE ){
			
			if( userInput && !userInput->hoverCapable() ){
				
				unordered_map< unsigned long, unsigned long >::iterator testPrevit = (UID_PointID_UIComp_Map[pointEvent->getUserID()]).find(pointEvent->getPointID());
				if(testPrevit != (UID_PointID_UIComp_Map[pointEvent->getUserID()]).end()){
					if( testPrevit->second ){						
						UserID_Type targetUID = getTenUI()->getUIComponent(testPrevit->second)->getOwnerUserID();
						
						if( targetUID == pointEvent->getPointID() ){							
							// Send Out Event
							pointEvents->push_back(
									sp<PointEvent>(
											new PointEvent(	PointEvent::OUT_EVENT_TYPE,
															pointEvent->getUserID(), 
															pointEvent->getUserInputID(), 
															pointEvent->getPointID(),
															pointEvent->getX(),
															pointEvent->getY(),
															pointEvent->getPressed(),
															getTenUI()->getUIComponent(testPrevit->second)
											)
									)
							);

							testPrevit->second = 0;
						}
					}

				}				
			}
		}else if(pointEvent->getType() == PointEvent::DOWN_EVENT_TYPE ){
			if( userInput && !userInput->hoverCapable() ){ 
				
				if( curTarget ){				
					unordered_map< unsigned long, unsigned long >::iterator testPrevit = (UID_PointID_UIComp_Map[pointEvent->getUserID()]).find(pointEvent->getPointID());
					if(testPrevit == (UID_PointID_UIComp_Map[pointEvent->getUserID()]).end()){
						
						if( curTarget->getOwnerUserID() == 0 ){
							// Send Out Event
							pointEvents->push_back(
									sp<PointEvent>(
											new PointEvent(	PointEvent::IN_EVENT_TYPE,
															pointEvent->getUserID(), 
															pointEvent->getUserInputID(), 
															pointEvent->getPointID(),
															pointEvent->getX(),
															pointEvent->getY(),
															pointEvent->getPressed(),
															curTarget
											)
									)
							);
							(UID_PointID_UIComp_Map[pointEvent->getUserID()])[pointEvent->getPointID()] = curTarget->getObjectID();
						}
					}
				}
			}
		}
		
		
		if( curTarget ){
			pointEvent->setTarget(curTarget);
			pointEvents->push_back(pointEvent);
		}

			
		
			
		return pointEvents;
	}
	
	void InputManager::handleInputEvent(const sp<Event> &evt){
		sp<PointEvent> pointEvent = dynamic_pointer_cast<PointEvent>(evt);
		if( pointEvent ){

			sp< vector< sp<PointEvent> > > eventsToDispatch = handlePointEvent(pointEvent);
			for( vector< sp<PointEvent> >::iterator it = eventsToDispatch->begin();
				 it != eventsToDispatch->end();
				 ++it){
				
				(*it)->getTarget()->handleUserInputEvent((*it));
			}			
		}else{

			sp<MultiPointEvent> multiEvent = dynamic_pointer_cast<MultiPointEvent>(evt);
			
			if( multiEvent ){

				unordered_map<UserID_Type, unordered_map<DisplayObjectIDType, sp<MultiPointEvent> > > userCompEvMap;
				
				for(MultiPointEvent::PointEventSetType::iterator it = multiEvent->getPointEvents()->begin();
					 it != multiEvent->getPointEvents()->end();
					 ++it){
					
					sp< vector< sp<PointEvent> > > pointEvents = handlePointEvent( (*it) );
					
					for(vector< sp<PointEvent> >::iterator pit = pointEvents->begin();
						pit != pointEvents->end();
						++pit){
						
						
						sp<MultiPointEvent> mpe;
						if( !userCompEvMap[(*pit)->getUserID()][(*pit)->getTarget()->getObjectID()] ){
							mpe = sp<MultiPointEvent>(new MultiPointEvent(multiEvent->getUserID(), multiEvent->getUserInputID()));
							userCompEvMap[(*pit)->getUserID()][(*pit)->getTarget()->getObjectID()] = mpe;
						}else{
							mpe = userCompEvMap[(*pit)->getUserID()][(*pit)->getTarget()->getObjectID()];
						}
						mpe->addPointEvent((*pit)); 
					}
				}
				
				for(unordered_map< UserID_Type, unordered_map< DisplayObjectIDType, sp<MultiPointEvent> > >::iterator it2 = userCompEvMap.begin();
					it2 != userCompEvMap.end();
					++it2){
					
					for(unordered_map<unsigned long, sp<MultiPointEvent> >::iterator mit = it2->second.begin();
						mit != it2->second.end();
						++mit){
						getTenUI()->getUIComponent(mit->first)->handleUserInputEvent(mit->second);
					}

				}
			}
		}
	}
	
	void InputManager::registerInput( const sp<UserInput>& ui){
				
		if(ui){
			inputs[ui->getUserInputID()] = ui;
		}
		
		ui->registerAllEventsHandler(&InputManager::handleInputEvent,InputManager::inst);
	}

}
