#include "UpState.h"
#include "HoverState.h"
#include "DownState.h"


#include <tr1/memory>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

#include <iostream>

using std::cout;
using std::endl;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
namespace ButtonStates{

	const string UpState::STATE_NAME = "Start";

	UpState::UpState(const shared_ptr<UIComponent>& _uiComp, const string& _stateName)
		:UIComponentState(_uiComp,_stateName){}
	UpState::~UpState(){}
	
	void UpState::handleMultiPointEvent(const shared_ptr<Event>& uievent ){
		//cout << "handleMultiPointEvent" << endl;
		shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
				it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == STATE_NAME;
				++it){
				if((*it)->getType() == PointEvent::IN_EVENT_TYPE){
					handlePointIn((*it));
				}else if((*it)->getType() == PointEvent::DOWN_EVENT_TYPE){
					handlePointIn((*it));
				}
			}
		}
	}
	
	void UpState::handlePointIn(const shared_ptr<Event>& uievent ){

		shared_ptr<PointEvent> pte = dynamic_pointer_cast<PointEvent>(uievent);
		if(pte){					
			// Multi User Support
			getUIComponent()->setOwnerUserID(pte->getPointID());

			shared_ptr<PointEvent> pe = dynamic_pointer_cast<PointEvent>(uievent);
			if( pe ){
				initX = getUIComponent()->getGlobalCenterX() - pe->getX();
				initY = getUIComponent()->getGlobalCenterY() - pe->getY();
			}
			
			if(pte->getPressed()){
				exitState(DownState::STATE_NAME);
			}else{
				exitState(HoverState::STATE_NAME);
			}

		}

	}
	
	void UpState::onEnter(const StateIDType& prevState){
		// Multi User Support
		getUIComponent()->clearOwnerUserID();
		
		initX = -1;
		initY = -1;

		getUIComponent()->registerHandler(
				PointEvent::IN_EVENT_TYPE, 
				&UpState::handlePointIn , 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				PointEvent::DOWN_EVENT_TYPE, 
				&UpState::handlePointIn , 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				&UpState::handleMultiPointEvent , 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
	}
	
	void UpState::onExit(const StateIDType& nextState){		
		getUIComponent()->unregisterHandler(
				PointEvent::IN_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				PointEvent::DOWN_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
	}
	

	int UpState::getInitiatingX(){
		return initX;
	}
	int UpState::getInitiatingY(){
		return initY;
	}
	
	
}}