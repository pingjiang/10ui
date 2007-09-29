#ifndef RECTANGLE_H_
#define RECTANGLE_H_


// includes
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "SDL.h"
#include "SDL_image.h"

#include "Shape.h"

#include <math.h>
#include <string>
#include <list>

namespace TenMilManUI_Graphics_Vector {
		
	class Rectangle : public Shape {	
	protected:
		double left;
		double bottom;
		
		// Sizing
		int w;
		int h;
		
	public:
		// constructor
		Rectangle(DisplayObject *p, int x=0, int y=0, int w=0, int h=0, float r=0.0, float g=0.0, float b=0.0, float sr=0.0, float sg=0.0, float sb=0.0, float strSize=0.0, double rot=0.0, double s=1.0, double o=1.0)
			:Shape(p,x,y,r,g,b,sr,sg,sb,strSize,rot,s,o){			
			this->setW(w);
			this->setH(h);
		}	
		virtual ~Rectangle(){}
			
		// game loop (and init) function
		virtual void init(){}
		virtual void update(){}	
		virtual void draw(){
			if( isEnable ){
				glPushMatrix();
					
				//cx = (cx * this->parent->getScaleX());
				//cy = (cy * this->parent->getScaleY());
								
				// translate, rotate, scale
				glTranslated((GLdouble)centerx,(GLdouble)centery,0);
				glRotatef((GLfloat)rotation,0,0,1);
				glScalef((GLfloat)this->scalex,(GLfloat)this->scaley,1.0);
				
				// this is for retrieving the mouse coords later
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
				glGetDoublev( GL_PROJECTION_MATRIX, projection );
				glGetIntegerv( GL_VIEWPORT, viewport );
		
				// rectangle's color
				glColor4d(color[0], color[1], color[2],(GLfloat)this->opacity);
						
				// draw rectangle
				glBegin(GL_QUADS);		                
					glVertex2d(left,bottom);
					glVertex2d(left,bottom+h);
					glVertex2d(left+w,bottom+w);
					glVertex2d(left+w,bottom);
				glEnd();
				
				// rectangle's stroke
				glColor4f(strokeColor[0], strokeColor[1], strokeColor[2],(GLfloat)this->opacity);
				glLineWidth(strokeSize);
								
				// draw line
				glBegin(GL_LINE_STRIP);	
					glVertex2d(left,bottom);
					glVertex2d(left,bottom+h);
					glVertex2d(left+w,bottom+h);
					glVertex2d(left+w,bottom);
				glEnd();
					
				glPopMatrix();
			}
		}
		
		// getter/setter functions
		virtual void setX(int nx){
			Shape::setX(nx);
			
			// Recalculate centerx 
			centerx = (double)x+scalex*(double)w/2.0;
		}
		
		virtual void setY(int ny){
			Shape::setY(ny);
			
			// Recalculate centery
			centery = (double)y+scaley*(double)h/2.0;
		}
		
		virtual int getW(){
			return w;
		}
		
		virtual void setW(int nw){
			left = -(double)nw/2.0;
			w = nw;
		}
		
		virtual int getH(){
			return h;
		}
		
		virtual void setH(int nh){
			bottom = -(double)nh/2.0;
			h = nh;
		}
		
	};

}
#endif /*RECTANGLE_H_*/
