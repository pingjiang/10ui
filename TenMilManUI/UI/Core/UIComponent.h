#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"
#include "../Events/EventHandler.h"

namespace TenUI {	
	class UIComponent : public DisplayObjectContainer, public EventHandler {
	public:
		UIComponent(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObjectContainer(p, x, y, w, h, rot,s,o){
		}
		
		virtual ~UIComponent(){};
		
		static std::string CLICK_EVENT;
		static std::string PRESS_EVENT;
		static std::string UNPRESS_EVENT;
		static std::string HOVER_IN_EVENT;
		static std::string HOVER_OUT_EVENT;
		static std::string HOVER_MOVE_EVENT;
	};
}

#endif /*UICOMPONENT_H_*/
