#ifndef SHAPE_H_
#define SHAPE_H_

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

namespace TenUI {
		
	class Shape : public DisplayObject {	
	protected:
		float color[3];
		
		float strokeColor[4];
		float strokeSize;
	
	public:	
		// constructor
		Shape(DisplayObject *p, int x=0, int y=0, float r=0.0, float g=0.0, float b=0.0, float sr=0.0, float sg=0.0, float sb=0.0, float strSize=5.0, double rot=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,0,0,rot,s,o){
			
			color[0] = r;
			color[1] = g;
			color[2] = b;
			
			strokeColor[0] = sr;
			strokeColor[1] = sg;
			strokeColor[2] = sb;
			strokeColor[3] = 1.0;
			
			strokeSize = strSize;
		}	
		virtual ~Shape(){}
		
		void setFillColor(float r=0.0, float g=0.0, float b=0.0)
		{
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}
		
		void setStrokeColor(float r=0.0, float g=0.0, float b=0.0)
		{
			strokeColor[0] = r;
			strokeColor[1] = g;
			strokeColor[2] = b;
		}
		
		void getFillColor(float &r, float &g, float &b)
		{
			r = color[0];
			g = color[1];
			b = color[2];
		}
		
		void getStrokeColor(float &r, float &g, float &b)
		{
			r = strokeColor[0];
			g = strokeColor[1];
			b = strokeColor[2];
		}
		
		
	};

}
#endif /*SHAPE_H_*/
