#include "UIComponentState.h"

namespace TenUI {

	void UIComponentState::setUIComponent(const sp<UIComponent>& uicomp){
		uiComponent = uicomp;
	}
	sp<UIComponent> UIComponentState::getUIComponent(){
		return uiComponent;
	}
}
