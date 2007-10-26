#include "UIComponent.h"
namespace TenUI{

	std::string UIComponent::CLICK_EVENT = "CLICK_EVENT";
	std::string UIComponent::PRESS_EVENT = "PRESS_EVENT";
	std::string UIComponent::UNPRESS_EVENT = "UNPRESS_EVENT";
	std::string UIComponent::HOVER_IN_EVENT = "HOVER_IN_EVENT";
	std::string UIComponent::HOVER_OUT_EVENT = "HOVER_OUT_EVENT";
	std::string UIComponent::HOVER_MOVE_EVENT = "HOVER_MOVE_EVENT";

	/***********************************/
	/*        Stylable Overrides       */
	/***********************************/
	void UIComponent::initStyles(){}

	/***********************************/
	/*        Init/Update Methods      */
	/***********************************/
	void UIComponent::init(){
		DisplayObjectContainer::init();
		initStyles();
	}
	
}
