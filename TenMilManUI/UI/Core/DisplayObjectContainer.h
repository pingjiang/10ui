#ifndef DISPLAYOBJECTCONTAINER_H_
#define DISPLAYOBJECTCONTAINER_H_

#include <vector>

#include "DisplayObject.h"		

#include <iostream>
using namespace std;

namespace TenUI {

	class DisplayObjectContainer : public DisplayObject {
	protected:
		vector<DisplayObject *> children;
	
	public:	
		// constructor
		DisplayObjectContainer(DisplayObject *p, int x=0, int y=0, unsigned int w=0, unsigned int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,w,h,rot,s,o){ cout << "DisplayObjectContainer(x,y):" << x << "," << y << endl; }
		virtual ~DisplayObjectContainer();
		
		/***********************************/
		/*     Hierarchy Getter/Setters    */
		/***********************************/  
		virtual void addChild(DisplayObject* child);		
		virtual void removeChild(DisplayObject* child);

		/***********************************/
		/*        Init/Update Methods      */
		/***********************************/
		virtual void init();
		virtual void update();
		virtual void deinit();	

		/***********************************/
		/*           Draw Methods          */
		/***********************************/
		virtual void preDraw();		
		virtual void draw();		
		virtual void postDraw();
		
	};
}

#endif /*DISPLAYOBJECTCONTAINER_H_*/
