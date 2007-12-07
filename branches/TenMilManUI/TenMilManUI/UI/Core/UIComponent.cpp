#include "UIComponent.h"
namespace TenUI{

	std::string UIComponent::CLICK_EVENT = "CLICK_EVENT";
	std::string UIComponent::PRESS_EVENT = "PRESS_EVENT";
	std::string UIComponent::UNPRESS_EVENT = "UNPRESS_EVENT";
	std::string UIComponent::HOVER_IN_EVENT = "HOVER_IN_EVENT";
	std::string UIComponent::HOVER_OUT_EVENT = "HOVER_OUT_EVENT";
	std::string UIComponent::HOVER_MOVE_EVENT = "HOVER_MOVE_EVENT";

	string UIComponent::getUIComponentName(){
		return "UIComponent";
	}

	/***********************************/
	/*        Stylable Overrides       */
	/***********************************/
	void UIComponent::initStyles(){
		StyleManager::instance()->registerUIComponent( dynamic_pointer_cast<UIComponent>(shared_from_this()), UIComponent::getUIComponentName(), "" );
		
	}

	void UIComponent::loadStyleSetMap(){
		stateStyleSetMap = StyleManager::instance()->getStateStyleSetMap( getUIComponentName() );
		curStyleSet = (*stateStyleSetMap)[StyleManager::DefaultStyleSetName];
	}

	/***********************************/
	/*        Init/Update Methods      */
	/***********************************/
	void UIComponent::init(){
		DisplayObjectContainer::init();
		initStyles();
		loadStyleSetMap();
	}
	
}
