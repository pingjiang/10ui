#ifndef DISPLAYOBJECTCONTAINER_H_
#define DISPLAYOBJECTCONTAINER_H_

#include <vector>

#include "DisplayObject.h"		

#include <iostream>
using namespace std;

namespace TenUI {

	class DisplayObjectContainer : public DisplayObject {
	protected:
		vector< shared_ptr<DisplayObject> > children;
	
	public:	
		// constructor
		DisplayObjectContainer( const shared_ptr<DisplayObject>& p, int x=0, int y=0, unsigned int w=0, unsigned int h=0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,w,h,rot,s,o){ }
		virtual ~DisplayObjectContainer();
		
		/***********************************/
		/*     Hierarchy Getter/Setters    */
		/***********************************/  
		virtual void addChild( shared_ptr<DisplayObject> child );		
		virtual void removeChild( shared_ptr<DisplayObject> child );
		virtual const vector< shared_ptr<DisplayObject> >& getChildren();

		/***********************************/
		/*        Init/Update Methods      */
		/***********************************/
		virtual void init();
		virtual void update();
		virtual void deinit();	


		/***********************************/
		/*      Extended Draw Methods      */
		/***********************************/
		// Self is always drawn before the Children
		// This makes it so children appear ontop of their Parent
		virtual void drawSelf() = 0;
		virtual void drawChildren();
		
		/***********************************/
		/*           Draw Methods          */
		/***********************************/
		virtual void draw();
		
		
	};
}

#endif /*DISPLAYOBJECTCONTAINER_H_*/
