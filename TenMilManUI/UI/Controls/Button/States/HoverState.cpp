#include "HoverState.h"

#include "UpState.h"
#include "DownState.h"

namespace TenUI{
namespace ButtonStates{

	const string HoverState::STATE_NAME = "Hover";

	HoverState::HoverState(const shared_ptr<UIComponent>& _uiComp)
		:UIComponentState(_uiComp,STATE_NAME){}
	HoverState::~HoverState(){}

	void HoverState::handlePointDown(const shared_ptr<Event>& uievent ){
		exitState(DownState::STATE_NAME);
	}
	void HoverState::handlePointOut(const shared_ptr<Event>& uievent ){
		exitState(UpState::STATE_NAME);
	}
	
	void HoverState::onEnter(const StateIDType& prevState){
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
	}
	
}}
