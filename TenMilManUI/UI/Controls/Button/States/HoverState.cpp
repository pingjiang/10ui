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

	const string HoverState::STATE_NAME = "Hover";
	
	
	HoverState::HoverState(const shared_ptr<UIComponent>& _uiComp)
		:UIComponentState(_uiComp,STATE_NAME),initX(-1),initY(-1){}
	HoverState::~HoverState(){}

	void HoverState::handleMultiPointEvent(const shared_ptr<Event>& uievent ){
		shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
		if(mpe){
			for(MultiPointEvent::PointEventSetType::iterator it = mpe->getPointEvents()->begin();
			it != mpe->getPointEvents()->end() && getUIComponent()->getCurState() == STATE_NAME;
				++it){
				
				// Only worry about the User that owns the UIComponent 
				if(getUIComponent()->getOwnerUserID() == (*it)->getUserID()){
					if((*it)->getType() == PointEvent::OUT_EVENT_TYPE){
						handlePointOut((*it));
					}else if((*it)->getType() == PointEvent::DOWN_EVENT_TYPE){
						handlePointDown((*it));
					}else if((*it)->getType() == ZoomPointEvent::ZOOM_EVENT_TYPE){
						handleZoom((*it));
					}
				}
			}
		}
	}
	void HoverState::handlePointDown(const shared_ptr<Event>& uievent ){
		shared_ptr<PointEvent> pe = dynamic_pointer_cast<PointEvent>(uievent);
		if( pe ){
			initX = getUIComponent()->getCenterX() - pe->getX();
			initY = getUIComponent()->getCenterY() - pe->getY();
		}
		exitState(DownState::STATE_NAME);
	}
	void HoverState::handlePointOut(const shared_ptr<Event>& uievent ){
		shared_ptr<PointEvent> pe = dynamic_pointer_cast<PointEvent>(uievent);
		if( pe ){
			initX = getUIComponent()->getCenterX() - pe->getX();
			initY = getUIComponent()->getCenterY() - pe->getY();
		}
		exitState(UpState::STATE_NAME);
	}
	void HoverState::handleZoom(const shared_ptr<Event>& uievent ){
		/*shared_ptr<ZoomPointEvent> zpe = dynamic_pointer_cast<ZoomPointEvent>(uievent);
		if(zpe){			
			cout << "HoverState" << endl;
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
				getUIComponent()->setW( getUIComponent()->getW() + zpe->getZoomAmount() );
				getUIComponent()->setH( getUIComponent()->getH() + zpe->getZoomAmount() );
		
				getUIComponent()->setCenterX(cx);
				getUIComponent()->setCenterY(cy);
				
				getUIComponent()->redraw();
			}
			
			
		}*/
	}
	
	void HoverState::onEnter(const StateIDType& prevState){

		getUIComponent()->registerHandler(
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				&HoverState::handleZoom , 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
		
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
				ZoomPointEvent::ZOOM_EVENT_TYPE, 
				dynamic_pointer_cast<HoverState>(shared_from_this())
		);
		
		
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