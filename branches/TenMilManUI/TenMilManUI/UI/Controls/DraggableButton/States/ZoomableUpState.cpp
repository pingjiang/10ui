#include "ZoomableUpState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>
#include <TenMilManUI/TenUI_Globals.h>

namespace TenUI{
namespace ButtonStates{

	const string ZoomableUpState::STATE_NAME = "Start";

	ZoomableUpState::ZoomableUpState(const shared_ptr<UIComponent>& _uiComp )
		:UpState(_uiComp,ZoomableUpState::STATE_NAME){}
	ZoomableUpState::~ZoomableUpState(){}

	//TODO Fix the extensibilty of this function 
	// Ideas: 	UserInputEventHandler/UserInputEventDispatcher (isolate events based on userid)
	//			UIComponentState::handleMultiPointEvent
	void ZoomableUpState::handleMultiPointEvent(const shared_ptr<Event>& uievent ){
		shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			
			/*if(mpe->getPointEvents()->size() == 2){
				cout << "GOT TWO" << endl;
			}*/
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
				it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == STATE_NAME;
				++it){
				if((*it)->getType() == PointEvent::IN_EVENT_TYPE){
					handlePointIn((*it));
				}else if((*it)->getType() == ZoomPointEvent::ZOOM_EVENT_TYPE){
					handleZoom((*it));
				}
			}
		}
	}
	void ZoomableUpState::handleZoom(const shared_ptr<Event>& uievent ){
	}
	
	void ZoomableUpState::onEnter(const StateIDType& prevState){
		UpState::onEnter(prevState);

		//getTenUI()->bringUIComponentFront(getUIComponent());
		
		// OVERRIDE handleMultiPointEvent
		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				dynamic_pointer_cast<UpState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE,
				&ZoomableUpState::handleMultiPointEvent, 
				dynamic_pointer_cast<ZoomableUpState>(shared_from_this())
		);
		
		
		getUIComponent()->registerHandler(
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				&ZoomableUpState::handleZoom, 
				dynamic_pointer_cast<ZoomableUpState>(shared_from_this())
		);
	}
	
	
	void ZoomableUpState::onExit(const StateIDType& nextState){
		UpState::onExit(nextState);

		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE,
				dynamic_pointer_cast<ZoomableUpState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				dynamic_pointer_cast<ZoomableUpState>(shared_from_this())
		);
	}
	
}}
