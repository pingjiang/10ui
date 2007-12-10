#ifndef UICOMPONENT_STATE_H_
#define UICOMPONENT_STATE_H_

#include <string>
#include <tr1/memory>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/State/State.h>

using std::string;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
	
	class UIComponentState : public State {
	public:
		static const string STATE_NAME;
		
	public:
		UIComponentState(const shared_ptr<UIComponent>& _uiComp,const string& _name)
			:State(_uiComp->getStateMachine(),_name),
			uiComponent(_uiComp){}
		virtual ~UIComponentState(){}
		
		shared_ptr<UIComponent> getUIComponent(){
			return uiComponent;
		}
		
		virtual void onEnter(const StateIDType& prevState){}
		virtual void onExit(const StateIDType& nextState){}
		
		virtual void update(){}
		
	private:
		shared_ptr<UIComponent> uiComponent;
		
	};
	
}

#endif /*UICOMPONENT_STATE_H_*/
