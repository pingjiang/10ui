#ifndef INTERACTIVEOBJECT_H_
#define INTERACTIVEOBJECT_H_

#include "../../Graphics/DisplayObject.h"

namespace TenUI {	

	class InteractiveObject : public DisplayObject {
	protected:					
	public:	
		// constructor
		InteractiveObject(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,rot,s,o){
			setX(x);
			setY(y);
			setW(w);
			setH(h);	
		}	
		virtual ~InteractiveObject(){}
	};
}
#endif /*INTERACTIVEOBJECT_H_*/
