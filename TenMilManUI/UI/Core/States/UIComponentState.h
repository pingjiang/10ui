#ifndef UICOMPONENT_STATE_H_
#define UICOMPONENT_STATE_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/State/State.h>

#include "UIComponentStateMacros.h"

using std::string;

namespace TenUI{

	class UIComponent;

	class UIComponentState : public State {
	DECL_STATE(UIComponentState, State, Start)
		
	public:
		virtual ~UIComponentState(){}

		void setUIComponent(const sp<UIComponent>& uicomp);
		sp<UIComponent> getUIComponent();
		
		virtual void onEnter(const StateIDType& prevState){}
		virtual void onExit(const StateIDType& nextState){}
		
		virtual void update(){}
		
	private:
		sp<UIComponent> uiComponent;
		
	};
	
}

#endif /*UICOMPONENT_STATE_H_*/
