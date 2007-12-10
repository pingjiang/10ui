#include "DownState.h"

#include "HoverState.h"
#include "UpState.h"

namespace TenUI{
namespace ButtonStates{

	const string DownState::STATE_NAME = "Down";

	DownState::DownState(const shared_ptr<UIComponent>& _uiComp )
		:UIComponentState(_uiComp,DownState::STATE_NAME){}
	DownState::~DownState(){}

	void DownState::handlePointUp(const shared_ptr<Event>& uievent ){
		exitState(HoverState::STATE_NAME);
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
	}
	
}}
