#include "UIComponent.h"
#include "States/UIComponentState.h"

#include <tr1/memory>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>

#include "Transitions/UIComponentTransition.h"

using std::tr1::dynamic_pointer_cast;

namespace TenUI{

	string UIComponent::getUIComponentName(){
		return "UIComponent";
	}

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
	}
	
	void UIComponent::handleUserInputEvent(const shared_ptr<UserInputEvent>& uievent){
		shared_ptr<PointEvent>pte = dynamic_pointer_cast<PointEvent>(uievent);
		if(pte){		
			dispatchEvent(pte);
		}else{
			shared_ptr<MultiPointEvent> mpe = dynamic_pointer_cast<MultiPointEvent>(uievent);
			dispatchEvent(mpe);
		}
	}

	/***********************************/
	/*              Event  		       */
	/***********************************/
	void UIComponent::initEvents(){
		addEventType(MultiPointEvent::MULTIPOINT_EVENT_TYPE);
		addEventType(PointEvent::DOWN_EVENT_TYPE);
		addEventType(PointEvent::UP_EVENT_TYPE);
		addEventType(PointEvent::MOVE_EVENT_TYPE);
		addEventType(PointEvent::IN_EVENT_TYPE);
		addEventType(PointEvent::OUT_EVENT_TYPE);
	}
	
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	const string& UIComponent::getCurState(){
		return stateMachine->getCurState()->getID();
	}
	const shared_ptr<StateMachine>& UIComponent::getStateMachine(){
		return stateMachine;
	}

	void UIComponent::initStates(){
		stateMachine->registerState(
				shared_ptr<UIComponentState>(
						new UIComponentState(
								dynamic_pointer_cast<UIComponent>(shared_from_this()),
								UIComponentState::STATE_NAME
						)
				), 
				true);

		// add transitions
		stateMachine->registerTransition(
				shared_ptr<UIComponentTransition>(
						new UIComponentTransition(
								dynamic_pointer_cast<UIComponent>(shared_from_this()), 
								State::ANY_STATE, State::ANY_STATE
						)
				)
		);
	}

	/***********************************/
	/*              Style              */
	/***********************************/
	any UIComponent::getStateStyleValue(const StateIDType& stateid, const string& name){
		unordered_map< string, shared_ptr<StyleSet> >::iterator it = stateStyleSetMap->find(stateid);
		if( it!=stateStyleSetMap->end() ){
			return it->second->getValue(name);	
		}
		return any();
	}
	void UIComponent::setStateStyleValue(const StateIDType& stateid, const string& name, const any& newvalue){
		unordered_map< string, shared_ptr<StyleSet> >::iterator it = stateStyleSetMap->find(stateid);
		if( it!=stateStyleSetMap->end() ){
			return it->second->setValue(name, newvalue);	
		}
	}	
	any UIComponent::getStyleValue(const string& name){
		return curStyleSet->getValue(name);
	}
	void UIComponent::setStyleValue(const string& name, const any& newvalue){
		return curStyleSet->setValue(name, newvalue);
	}	
	void UIComponent::initStyles(){
		StyleManager::instance()->registerUIComponent( dynamic_pointer_cast<UIComponent>(shared_from_this()), UIComponent::getUIComponentName(), "" );
		
	}
	void UIComponent::loadStyleSetMap(){
		stateStyleSetMap = StyleManager::instance()->getStateStyleSetMap( getUIComponentName() );
		curStyleSet = (*stateStyleSetMap)[UIComponentState::STATE_NAME];
	}

	void UIComponent::setStyleSet(const string& styleSetName){
		unordered_map< string, shared_ptr<StyleSet> >::iterator it = stateStyleSetMap->find(styleSetName);
		if( it!=stateStyleSetMap->end() ){
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
	void UIComponent::init(){
		DisplayObjectContainer::init();
		
		clearOwnerUserID();
		
		initEvents();
		initStates();
		initStyles();
				
		loadStyleSetMap();
	}
	void UIComponent::update(){
		DisplayObjectContainer::update();
		
		stateMachine->updateStateMachine();
	}
	
}
