#ifndef DISPLAYOBJECTCONTAINER_H_
#define DISPLAYOBJECTCONTAINER_H_

#include <vector>

#include "InteractiveObject.h"

using namespace std;

namespace TenMilManUI_UI {	

	class DisplayObjectContainer : public InteractiveObject {
	protected:
		vector<DisplayObject *> children; 
		
		double centerx;
		double centery;
		
	public:	
		// constructor
		DisplayObjectContainer(DisplayObject *p, int x=0, int y=0, double rot=0.0, double s=1.0, double o=1.0)
			:InteractiveObject(p,x,y,rot,s,o){}	
		virtual ~DisplayObjectContainer(){
			children.clear();
		}
			
		// game loop (and init) function
		virtual void draw(){
			if( isEnable ){
				glPushMatrix();
		
				// translate, rotate, scale
				glTranslated((GLdouble)x,(GLdouble)y,0);
				glRotatef((GLfloat)rotation,0,0,1);
				glScalef((GLfloat)this->scalex,(GLfloat)this->scaley,1.0);
				
				// this is for retrieving the mouse coords later
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
				glGetDoublev( GL_PROJECTION_MATRIX, projection );
				glGetIntegerv( GL_VIEWPORT, viewport );
				
				vector<DisplayObject *>::iterator it = children.begin();
				while(it != children.end()){
					(*it)->draw();
				}
		
				glPopMatrix();
			}
		}
				
	};
}

#endif /*DISPLAYOBJECTCONTAINER_H_*/
