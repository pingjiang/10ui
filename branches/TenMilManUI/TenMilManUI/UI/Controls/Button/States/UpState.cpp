#include "UpState.h"
#include "HoverState.h"
#include "DownState.h"

#include <tr1/memory>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>

#include <iostream>

using std::cout;
using std::endl;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
namespace ButtonStates{

	const string UpState::STATE_NAME = "Start";

	UpState::UpState(const shared_ptr<UIComponent>& _uiComp )
		:UIComponentState(_uiComp,STATE_NAME){}
	UpState::~UpState(){}
	
	void UpState::handlePointIn(const shared_ptr<Event>& uievent ){
		shared_ptr<PointEvent> pte = dynamic_pointer_cast<PointEvent>(uievent);
		if(pte && pte->getPressed()){
			exitState(DownState::STATE_NAME);
		}else{
			exitState(HoverState::STATE_NAME);
		}
	}
	
	void UpState::onEnter(const StateIDType& prevState){
		getUIComponent()->registerHandler(
				PointEvent::IN_EVENT_TYPE, 
				&UpState::handlePointIn , 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
	}
	
	void UpState::onExit(const StateIDType& nextState){		
		getUIComponent()->unregisterHandler(
				PointEvent::IN_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
	}
	
}}
