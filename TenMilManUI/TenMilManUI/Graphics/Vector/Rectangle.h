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

namespace TenUI {
		
	class Rectangle : public Shape {	
	protected:		
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
			
			
			// rectangle's stroke
				glColor4f(strokeColor[0], strokeColor[1], strokeColor[2],(GLfloat)opacity*strokeColor[3]);
				
				// draw line
				glBegin(GL_QUADS);	            						
					glVertex2f((left-strokeSize),(bottom-strokeSize));
					glVertex2f((left-strokeSize),(bottom+h+strokeSize));
					glVertex2f((left+w+strokeSize),(bottom+h+strokeSize));
					glVertex2f((left+w+strokeSize),(bottom-strokeSize));
				glEnd();
			
			// rectangle's color
				glColor4d(color[0], color[1], color[2],(GLfloat)this->opacity);
				
				// draw rectangle
				glBegin(GL_QUADS);		

					glVertex2i((int)left,(int)bottom);
					glVertex2i((int)left,(int)(bottom+h));
					glVertex2i((int)(left+w),(int)(bottom+h));
					glVertex2i((int)(left+w),(int)(bottom));
					/*glVertex2i(100,100);
					glVertex2i(100,150);
					glVertex2i(150,150);
					glVertex2i(150,100);*/
				glEnd();

		}

	};

}
#endif /*RECTANGLE_H_*/
