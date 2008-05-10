#include "DragDownState.h"

#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>
#include <TenMilManUI/UI/Controls/Button/States/HoverState.h>
#include <TenMilManUI/UI/Controls/Button/States/UpState.h>
#include <TenMilManUI/TenUI_Globals.h>

#include <algorithm>

using std::max;
using std::min;
namespace TenUI{
namespace ButtonStates{
	DragDownState::~DragDownState(){}

	//TODO Fix the extensibilty of this function 
	// Ideas: 	UserInputEventHandler/UserInputEventDispatcher (isolate events based on userid)
	//			UIComponentState::handleMultiPointEvent
	void DragDownState::handleMultiPointEvent(const sp<Event>& uievent ){
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
					}else if((*it)->getType() == PointEvent::MOVE_EVENT_TYPE){
						handlePointMove((*it));
					}else if((*it)->getType() == ZoomPointEvent::ZOOM_EVENT_TYPE){
						handleZoom((*it));
					}
				}
			}
		}
	}
	void DragDownState::handlePointMove(const sp<Event>& uievent ){
		sp<PointEvent> pte = dynamic_pointer_cast<PointEvent>(uievent); 
		if(pte){
			getUIComponent()->setGlobalCenterX(pte->getX()+offsetX);
			getUIComponent()->setGlobalCenterY(pte->getY()+offsetY);
		}
		
	}
	void DragDownState::onEnter(const StateIDType& prevState){
		DownState::onEnter(prevState);

		if( prevState == HoverState::getStateName() ){
			sp<HoverState> hover = dynamic_pointer_cast<HoverState>(getUIComponent()->getStateMachine()->getState(prevState));
			offsetX = hover->getInitiatingX();
			offsetY = hover->getInitiatingY();
		}else if( prevState == UpState::getStateName() ){
			sp<UpState> hover = dynamic_pointer_cast<UpState>(getUIComponent()->getStateMachine()->getState(prevState));
			offsetX = hover->getInitiatingX();
			offsetY = hover->getInitiatingY();
		}
		
		getTenUI()->bringUIComponentFront(getUIComponent());
		
		// Get rid of the old one
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
		

		getUIComponent()->registerHandler(
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				&DragDownState::handleZoom, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
	}
	

	void DragDownState::handleZoom(const sp<Event>& uievent ){
		sp<ZoomPointEvent> zpe = dynamic_pointer_cast<ZoomPointEvent>(uievent);
		if(zpe){
				cout << "DragDownState" << endl;
				bool doit = false;
				
				if( zpe->getZoomAmount() < 0 &&  
					getUIComponent()->getH() > 50 &&
					getUIComponent()->getW() > 50 ){
					
					doit = true;
				}else if( zpe->getZoomAmount() > 0 &&  
						getUIComponent()->getH() < 500 &&
						getUIComponent()->getW() < 500 ){
					doit = true;
				}
				
				if(doit){
					int cx = getUIComponent()->getCenterX();
					int cy = getUIComponent()->getCenterY();
					double sum = (double)getUIComponent()->getW()+(double)getUIComponent()->getH();
					double wratio = (double)getUIComponent()->getW() / sum;
					double hratio = (double)getUIComponent()->getH() / sum;
										
					getUIComponent()->setW( max(50, min(500,(int)getUIComponent()->getW() + (int)(zpe->getZoomAmount()*wratio))) );
					getUIComponent()->setH( max(50, min(500,(int)getUIComponent()->getH() + (int)(zpe->getZoomAmount()*hratio))) );
			
					getUIComponent()->setCenterX(cx);
					getUIComponent()->setCenterY(cy);
					
					getUIComponent()->redraw();
				}
				
		}
	}
	
	
	void DragDownState::onExit(const StateIDType& nextState){
		DownState::onExit(nextState);
		getUIComponent()->unregisterHandler(
				MultiPointEvent::MULTIPOINT_EVENT_TYPE,
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
		getUIComponent()->unregisterHandler(
				PointEvent::MOVE_EVENT_TYPE, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);

		getUIComponent()->unregisterHandler(
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				dynamic_pointer_cast<DragDownState>(shared_from_this())
		);
	}
	
}}
