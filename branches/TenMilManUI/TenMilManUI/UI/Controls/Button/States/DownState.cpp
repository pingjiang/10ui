#include "DownState.h"

#include "HoverState.h"
#include "UpState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

namespace TenUI{
namespace ButtonStates{

	DownState::~DownState(){}

	void DownState::handleMultiPointEvent(const sp<Event>& uievent ){
		sp<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
			it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == getStateName();
				++it){

				// Only worry about the User that owns the UIComponent 
				if(getUIComponent()->getOwnerUserID() == (*it)->getPointID()){
					if((*it)->getType() == PointEvent::UP_EVENT_TYPE){
						handlePointUp((*it));
					}else if((*it)->getType() == PointEvent::OUT_EVENT_TYPE){
						handlePointOut((*it));
					}
				}
			}
		}
	}
	void DownState::handlePointUp(const sp<Event>& uievent ){
		exitState(UpState::getStateName());
	}
	void DownState::handlePointOut(const sp<Event>& uievent ){
		exitState(UpState::getStateName());
	}
	
	void DownState::onEnter(const StateIDType& prevState){
		getUIComponent()->registerHandler(
				PointEvent::UP_EVENT_TYPE, 
				&DownState::handlePointUp , 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				PointEvent::OUT_EVENT_TYPE, 
				&DownState::handlePointOut , 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);

		getUIComponent()->registerHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				&DownState::handleMultiPointEvent , 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);
	}
	
	void DownState::onExit(const StateIDType& nextState){
		getUIComponent()->unregisterHandler(
				PointEvent::OUT_EVENT_TYPE, 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				PointEvent::UP_EVENT_TYPE, 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);
	}
	
}}
