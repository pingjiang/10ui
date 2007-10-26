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
#include <iostream>
using namespace std;

namespace TenUI {	

	class Line : public DisplayObject {
	protected:
		int 	x2, y2;
		float	lineColor[3];
		float 	lineWidth;
		
		virtual void calcCenterX(){
			centerx = (double)((x2>x)?x:x2)+scalex*(double)w/2.0;
		}

		virtual void calcCenterY(){
			centery = (double)((y2>y)?y:y2)+scaley*(double)h/2.0;
		}
		
	public:	
		// constructor
		Line(DisplayObject *p, 	int x=0, int y=0, int x2=0, int y2=0, 
								float r=0.0, float g=0.0, float b=0.0, 
								float lineWidth=0.0, 
								double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,rot,s,o){			
			
			setX(x);			
			setY(y);
			setX2(x2);			
			setY2(y2);
			
			lineColor[0]=r;
			lineColor[1]=g;
			lineColor[2]=b;

			this->lineWidth = lineWidth;
		}	
		virtual ~Line(){}
			
		// game loop (and init) function
		virtual void init(){}
		virtual void update(){}	
		
		void preDraw(){
			DisplayObject::preDraw();
			
			glEnable(GL_SCISSOR_TEST);
			
			//int gx;
			//int gy;
			//localToGlobalCoord(left, bottom, &gx, &gy);
			
			glScissor(	getGlobalX()-((x2>x)?0:w), 
						getGlobalY()-((y2>y)?0:h), 
						w, 
						h);
									
		}
		virtual void draw(){
			glColor4f(lineColor[0], lineColor[1], lineColor[2],(GLfloat)this->opacity);
			glLineWidth(lineWidth);

			// draw line
			glBegin(GL_LINES);				
				glVertex2d((GLdouble)((x2>x)?left:left+w),(GLdouble)((y2>y)?bottom:bottom+h));
				glVertex2d((GLdouble)((x2>x)?left+w:left),(GLdouble)((y2>y)?bottom+h:bottom));					
			glEnd();
		}
		void postDraw(){
			glDisable(GL_SCISSOR_TEST);

			DisplayObject::postDraw();
		}
		
		int getX2(){
			return x2;
		}
		
		int getY2(){
			return y2;
		}
		

		virtual void setX(int nx){	
			x = nx;
						
			// Recalculate centerx 
			centerx = (double)((x2>x)?x:x2)+scalex*(double)w/2.0;
		}	

		virtual void setY(int ny){
			y = ny;
			
			// Recalculate centery
			centery = (double)((y2>y)?y:y2)+scaley*(double)h/2.0;
		}
		
		void setX2(int nx){
			x2 = nx;
			DisplayObject::setW((x2>x)?x2-x:x-x2);
		}
		
		void setY2(int ny){
			y2 = ny;
			DisplayObject::setH((y2>y)?y2-y:y-y2);
		}				
		
		virtual void setW(int nw){
			DisplayObject::setW(nw);
			x2 = x+nw;
		}

		virtual void setH(int nh){
			DisplayObject::setH(nh);
			y2 = y+nh;
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
