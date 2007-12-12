#include "DragDownState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

namespace TenUI{
namespace ButtonStates{

	const string DragDownState::STATE_NAME = "Down";

	DragDownState::DragDownState(const shared_ptr<UIComponent>& _uiComp )
		:DownState(_uiComp,DragDownState::STATE_NAME){}
	DragDownState::~DragDownState(){}

	//TODO Fix the extensibilty of this function 
	// Ideas: 	UserInputEventHandler/UserInputEventDispatcher (isolate events based on userid)
	//			UIComponentState::handleMultiPointEvent
	void DragDownState::handleMultiPointEvent(const shared_ptr<Event>& uievent ){
		shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
			it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == STATE_NAME;
				++it){

				// Only worry about the User that owns the UIComponent 
				if(getUIComponent()->getOwnerUserID() == (*it)->getUserID()){
					if((*it)->getType() == PointEvent::UP_EVENT_TYPE){
						handlePointUp((*it));
					}else if((*it)->getType() == PointEvent::OUT_EVENT_TYPE){
						handlePointOut((*it));
					}else if((*it)->getType() == PointEvent::MOVE_EVENT_TYPE){
						handlePointMove((*it));
					}
				}
			}
		}
	}
	void DragDownState::handlePointMove(const shared_ptr<Event>& uievent ){
		shared_ptr<PointEvent> pte = dynamic_pointer_cast<PointEvent>(uievent); 
		if(pte){
			getUIComponent()->setCenterX(pte->getX());
			getUIComponent()->setCenterY(pte->getY());
		}
		
	}
	void DragDownState::onEnter(const StateIDType& prevState){
		DownState::onEnter(prevState);

		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE, 
				dynamic_pointer_cast<DownState>(shared_from_this())
		);

		getUIComponent()->registerHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE,
				&DragDownState::handleMultiPointEvent, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
		getUIComponent()->registerHandler(
				PointEvent::MOVE_EVENT_TYPE, 
				&DragDownState::handlePointMove, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
	}
	
	
	void DragDownState::onExit(const StateIDType& nextState){
		DownState::onExit(nextState);
		getUIComponent()->unregisterHandler(
				PointEvent::MOVE_EVENT_TYPE, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
	}
	
}}
