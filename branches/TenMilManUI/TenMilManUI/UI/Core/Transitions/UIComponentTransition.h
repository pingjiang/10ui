#ifndef UICOMPONENTTRANSITION_H_
#define UICOMPONENTTRANSITION_H_

#include "../UIComponent.h"
#include <TenMilManUI/UI/State/Transition.h>

namespace TenUI{
	
	class UIComponent;

	class UIComponentTransition : public Transition {
	public:
		UIComponentTransition(const StateIDType& _from, const StateIDType& _to);
		
		bool update();
		
		void setUIComponent(const sp<UIComponent>& uicomp);
		sp<UIComponent> getUIComponent();
		
		virtual sp<UIComponentTransition> clone(){return sp<UIComponentTransition>();}
		
	protected:
		sp<UIComponent> uicomp;
	};
	
}

#endif /*UICOMPONENTTRANSITION_H_*/
