#include "UIComponentTransition.h"
#include <iostream>
using std::cout;
using std::endl;


namespace TenUI{

	UIComponentTransition::UIComponentTransition(const StateIDType& _from, const StateIDType& _to)
		:Transition(_from, _to){}
	
	bool UIComponentTransition::update(){
		uicomp->setStyleSet(specificTo);
		return false;
	}
	
	sp<UIComponent> UIComponentTransition::getUIComponent(){
		return uicomp;
	}

	void UIComponentTransition::setUIComponent(const sp<UIComponent>& _uicomp){
		uicomp = _uicomp;
		setStateMachine(uicomp->getStateMachine());
	}
}
