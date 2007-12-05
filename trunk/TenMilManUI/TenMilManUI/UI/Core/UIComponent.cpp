#include "UIComponent.h"
//#include "../Managers/SelectManager.h"

using std::string;

namespace TenUI {

	UIComponent::UIComponent(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, double rot=0.0, double s=1.0, double o=1.0)
	:DisplayObjectContainer(p, x, y, w, h, rot,s,o) {
	}
	
	UIComponent::~UIComponent(){	
	}
	
	//TODO: Should probably be removed
	string UIComponent::CLICK_EVENT			= "CLICK_EVENT";
	string UIComponent::PRESS_EVENT			= "PRESS_EVENT";
	string UIComponent::UNPRESS_EVENT		= "UNPRESS_EVENT";
	string UIComponent::HOVER_IN_EVENT		= "HOVER_IN_EVENT";
	string UIComponent::HOVER_OUT_EVENT		= "HOVER_OUT_EVENT";
	string UIComponent::HOVER_MOVE_EVENT	= "HOVER_MOVE_EVENT";

	string UIComponent::DRAG_ENTER			= "DRAG_ENTER";
	string UIComponent::DRAG_MOVE			= "DRAG_MOVE";
	string UIComponent::DRAG_START			= "DRAG_START";
	string UIComponent::DRAG_EXIT			= "DRAG_EXIT";
	string UIComponent::DRAG_DROP			= "DRAG_DROP";
	string UIComponent::DRAG_COMPLETE		= "DRAG_COMPLETE";
}
