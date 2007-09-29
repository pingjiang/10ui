#ifndef LINE_H_
#define LINE_H_

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

#include "../DisplayObject.h"

#include <math.h>
#include <string>
#include <list>

namespace TenMilManUI_Graphics_Vector {	

	class Line : public DisplayObject {
	protected:
		int 	x2, y2;
		float	lineColor[3];
		float 	lineWidth;
		
	public:	
		// constructor
		Line(DisplayObject *p, int x=0, int y=0, int x2=0, int y2=0, float r=0.0, float g=0.0, float b=0.0, float lineWidth=0.0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,rot,s,o){			
			
			this->x2 = x2;			
			this->y2 = y2;
			
			lineColor[0]=r;
			lineColor[1]=g;
			lineColor[2]=b;

			this->lineWidth = lineWidth;
		}	
		virtual ~Line(){}
			
		// game loop (and init) function
		virtual void init(){}
		virtual void update(){}	
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
		
				glColor4f(lineColor[0], lineColor[1], lineColor[2],(GLfloat)this->opacity);
				glLineWidth(lineWidth);
								
				// draw line
				glBegin(GL_LINES);		                
					glVertex2d((GLdouble)0,(GLdouble)0);
					glVertex2d((GLdouble)x2-x,(GLdouble)y2-y);					
				glEnd();
				
				glPopMatrix();
			}
		}
		
		int getX2(){
			return x2;
		}
		
		int getY2(){
			return y2;
		}
		
		void setX2(int nx){
			x2 = nx;
		}
		
		void setY2(int ny){
			y2 = ny;
		}
		
		const float* getLineColor(){
			return lineColor;
		}

		void setLineColor(float r, float g, float b){
			lineColor[0] = r;
			lineColor[1] = g;
			lineColor[2] = b;
		}
		
		void setLineColor(float (&colors)[3]){
			lineColor[0] = colors[0];
			lineColor[1] = colors[1];
			lineColor[2] = colors[2];
		}
		
		float getLineWidth(){
			return lineWidth;
		}
		
		void setLineWidth(float lw){
			lineWidth = lw;
		}
				
	};

}
#endif /*LINE_H_*/
