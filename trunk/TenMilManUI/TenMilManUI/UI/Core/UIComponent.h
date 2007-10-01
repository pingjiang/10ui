#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"

namespace TenMilManUI_CORE_UI_Core {	
	class UIComponent : public DisplayObjectContainer {
	public:
		UIComponent(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObjectContainer(p, x, y, w, h, rot,s,o){
		}
		
		virtual ~UIComponent(){};
	};
}

#endif /*UICOMPONENT_H_*/
