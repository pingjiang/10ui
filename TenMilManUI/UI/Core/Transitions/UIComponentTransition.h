#ifndef UICOMPONENTTRANSITION_H_
#define UICOMPONENTTRANSITION_H_

#include "../UIComponent.h"
#include <TenMilManUI/UI/State/Transition.h>

namespace TenUI{
	
	class UIComponent;

	class UIComponentTransition : public Transition {
	public:
		UIComponentTransition(const shared_ptr<UIComponent>& _uicomp, const StateIDType& _from, const StateIDType& _to);
		
		bool update();
		
		shared_ptr<UIComponent> getUIComponent();
		
	protected:
		shared_ptr<UIComponent> uicomp;
	};
	
}

#endif /*UICOMPONENTTRANSITION_H_*/
