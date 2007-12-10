#include "UIComponentTransition.h"
#include <iostream>
using std::cout;
using std::endl;


namespace TenUI{

	UIComponentTransition::UIComponentTransition(const shared_ptr<UIComponent>& _uicomp, const StateIDType& _from, const StateIDType& _to)
		:Transition(_uicomp->getStateMachine(), _from, _to),
		 uicomp(_uicomp){}
	
	bool UIComponentTransition::update(){
		uicomp->setStyleSet(specificTo);
		return false;
	}
	
	shared_ptr<UIComponent> UIComponentTransition::getUIComponent(){
		return uicomp;
	}
}
