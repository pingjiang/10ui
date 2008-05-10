#include "UIComponent.h"
#include "States/UIComponentState.h"

#include <tr1/memory>
#include <TenMilManUI/UI/Managers/UIComponentManager.h>
#include <TenMilManUI/UI/Managers/StateManager.h>
#include <TenMilManUI/UI/Managers/StyleManager.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

#include "Transitions/UIComponentTransition.h"

using std::tr1::dynamic_pointer_cast;

namespace TenUI{

	BEGIN_IMPL_EVENTS(UIComponent)
		IMPL_EVENT(UIComponent, MultiPointEvent)
		IMPL_EVENT(UIComponent, PointIn)
		IMPL_EVENT(UIComponent, PointOut)
		IMPL_EVENT(UIComponent, PointMove)
		IMPL_EVENT(UIComponent, PointUp)
		IMPL_EVENT(UIComponent, PointDown)
	END_IMPL_EVENTS(UIComponent)


	/***********************************/
	/*              Input  		       */
	/***********************************/
	UserID_Type	UIComponent::getOwnerUserID(){
		return ownerUserID;
	}
	void UIComponent::setOwnerUserID(UserID_Type newOwner){
		ownerUserID = newOwner;
	}
	UserID_Type UIComponent::clearOwnerUserID(){
		ownerUserID = 0;
		return ownerUserID;
	}
	
	void UIComponent::handleUserInputEvent(const sp<UserInputEvent>& uievent){
		dispatchEvent(uievent);
	}
	
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	StateIDType UIComponent::getStartStateID(){return UIComponentState::getStateName();}
	const string& UIComponent::getCurState(){
		return stateMachine->getCurState()->getID();
	}
	const sp<StateMachine>& UIComponent::getStateMachine(){
		return stateMachine;
	}
	/***********************************/
	/*              Style              */
	/***********************************/
	void UIComponent::setAllStateStyleValue(const string& name, const any& newvalue){
		for(unordered_map< StateIDType, sp<StyleSet> >::iterator it = stateStyleSetMap.begin();
			it != stateStyleSetMap.end();
			++it){
			it->second->setValue(name, newvalue);	
		}
	}
	any UIComponent::getStateStyleValue(const StateIDType& stateid, const string& name){
		unordered_map< StateIDType, sp<StyleSet> >::iterator it = stateStyleSetMap.find(stateid);
		if( it!=stateStyleSetMap.end() ){
			return it->second->getValue(name);	
		}
		return any();
	}
	void UIComponent::setStateStyleValue(const StateIDType& stateid, const string& name, const any& newvalue){
		unordered_map< StateIDType, sp<StyleSet> >::iterator it = stateStyleSetMap.find(stateid);
		if( it!=stateStyleSetMap.end() ){
			return it->second->setValue(name, newvalue);	
		}
	}	
	any UIComponent::getStyleValue(const string& name){
		return curStyleSet->getValue(name);
	}
	void UIComponent::setStyleValue(const string& name, const any& newvalue){
		return curStyleSet->setValue(name, newvalue);
	}

	void UIComponent::setStyleSet(const string& styleSetName){
		unordered_map< string, sp<StyleSet> >::iterator it = stateStyleSetMap.find(styleSetName);
		if( it!=stateStyleSetMap.end() ){
			curStyleSet = it->second;
			redraw();
		}
	}

	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/

	void UIComponent::drawSelf(){
		//DisplayObjectContainer::drawSelf();
	}
	void UIComponent::update(){
		DisplayObjectContainer::update();
		
		stateMachine->updateStateMachine();
	}

	void UIComponent::init(){
		DisplayObjectContainer::init();
	}

}
