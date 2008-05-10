#include "HoverState.h"


#include "UpState.h"
#include "DownState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>
#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>

#include <iostream>
using std::cout;
using std::endl;

namespace TenUI{
namespace ButtonStates{
	HoverState::~HoverState(){}

	void HoverState::handleMultiPointEvent(const sp<Event>& uievent ){
		sp<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
			it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == getStateName();
				++it){
				
				// Only worry about the User that owns the UIComponent 
				if(getUIComponent()->getOwnerUserID() == (*it)->getPointID()){
					if((*it)->getType() == PointEvent::OUT_EVENT_TYPE){
						handlePointOut((*it));
					}else if((*it)->getType() == PointEvent::DOWN_EVENT_TYPE){
						handlePointDown((*it));
					}
				}
			}
		}
	}
	void HoverState::handlePointDown(const sp<Event>& uievent ){
		sp<PointEvent> pe = dynamic_pointer_cast<PointEvent>(uievent);
		if( pe ){
			initX = getUIComponent()->getGlobalCenterX() - pe->getX();
			initY = getUIComponent()->getGlobalCenterY() - pe->getY();
		}
		exitState(DownState::getStateName());
	}
	void HoverState::handlePointOut(const sp<Event>& uievent ){
		exitState(UpState::getStateName());
	}
	
	void HoverState::onEnter(const StateIDType& prevState){
		cout << "HoverState::onEnter()" << endl;
		
		getUIComponent()->registerHandler(
				PointEvent::OUT_EVENT_TYPE, 
				&HoverState::handlePointOut , 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				PointEvent::DOWN_EVENT_TYPE, 
				&HoverState::handlePointDown , 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);

		getUIComponent()->registerHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				&HoverState::handleMultiPointEvent , 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
	}
	
	void HoverState::onExit(const StateIDType& nextState){
		getUIComponent()->unregisterHandler(
				PointEvent::OUT_EVENT_TYPE, 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				PointEvent::DOWN_EVENT_TYPE, 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
	}
	

	int HoverState::getInitiatingX(){
		return initX;
	}
	int HoverState::getInitiatingY(){
		return initY;
	}
	
}}
