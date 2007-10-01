#ifndef DISPLAYOBJECTCONTAINER_H_
#define DISPLAYOBJECTCONTAINER_H_

#include <vector>

#include "../../Graphics/DisplayObject.h"			
#include "InteractiveObject.h"

using namespace std;

namespace TenMilManUI_CORE_UI_Core {	

	class DisplayObjectContainer : public InteractiveObject {
	protected:
		vector<DisplayObject *> children;
	
	public:	
		// constructor
		DisplayObjectContainer(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:InteractiveObject(p,x,y,w,h,rot,s,o){}
		virtual ~DisplayObjectContainer();
		
		// game loop (and init) function
		virtual void update();		
		virtual void preDraw();		
		virtual void draw();		
		virtual void postDraw();
		
		void addChild(DisplayObject* child);		
		void removeChild(DisplayObject* child);
	};
}

#endif /*DISPLAYOBJECTCONTAINER_H_*/
