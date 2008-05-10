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
	UpState::~UpState(){}
	
	void UpState::handleMultiPointEvent(const sp<Event>& uievent ){
		//cout << "handleMultiPointEvent" << endl;
		sp<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
				it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == getStateName();
				++it){
				if((*it)->getType() == PointEvent::IN_EVENT_TYPE){
					handlePointIn((*it));
				}else if((*it)->getType() == PointEvent::DOWN_EVENT_TYPE){
					handlePointIn((*it));
				}
			}
		}
	}
	
	void UpState::handlePointIn(const sp<Event>& uievent ){
		sp<PointEvent> pte = dynamic_pointer_cast<PointEvent>(uievent);
		if(pte){
			
			// Multi User Support
			getUIComponent()->setOwnerUserID(pte->getPointID());

			sp<PointEvent> pe = dynamic_pointer_cast<PointEvent>(uievent);
			if( pe ){
				initX = getUIComponent()->getGlobalCenterX() - pe->getX();
				initY = getUIComponent()->getGlobalCenterY() - pe->getY();
			}
			
			if(pte->getPressed()){
				exitState(DownState::getStateName());
			}else{
				exitState(HoverState::getStateName());
			}

		}else{
			cout << "\tNOT PointEvent" << endl;
		}

	}
	
	void UpState::onEnter(const StateIDType& prevState){
		cout << "UpState::onEnter()" << endl;
		
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
		cout << "UpState::onExit()" << endl;
		
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
