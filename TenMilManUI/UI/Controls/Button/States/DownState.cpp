#include "DownState.h"

#include "HoverState.h"
#include "UpState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

namespace TenUI{
namespace ButtonStates{

	const string DownState::STATE_NAME = "Down";

	DownState::DownState(const shared_ptr<UIComponent>& _uiComp, const string& stateName)
		:UIComponentState(_uiComp,stateName){}
	DownState::~DownState(){}

	void DownState::handleMultiPointEvent(const shared_ptr<Event>& uievent ){
		shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
			it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == STATE_NAME;
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
	void DownState::handlePointUp(const shared_ptr<Event>& uievent ){
		exitState(UpState::STATE_NAME);
	}
	void DownState::handlePointOut(const shared_ptr<Event>& uievent ){
		exitState(UpState::STATE_NAME);
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
