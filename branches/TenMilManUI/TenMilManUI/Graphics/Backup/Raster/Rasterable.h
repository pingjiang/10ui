#ifndef RASTERABLE_H_
#define RASTERABLE_H_

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
	enum RASTERABLE_EXCEPTIONS { SET_TEXTURE_FAILED };
		
	class Rasterable : public DisplayObject {	
	protected:
		int texw;
		int texh;
				
		// texture
		bool textureSet;
		GLuint texture;
		
		SDL_Surface *LoadTextureFromFile(const char *filename);
	
		// load bmps and convert to textures
		bool LoadGLTextures(const char *filename);
	
	public:	
		// constructor
		Rasterable(DisplayObject *p, int x=0, int y=0, double r=0.0, double s=1.0, double o=1.0);
		virtual ~Rasterable();
			
		// game loop (and init) function
		virtual void init();
		virtual void update();
		
		virtual void preDraw();		
		virtual void draw();
		virtual void postDraw();
		
		// getter/setter functions				
		// set functions
		virtual void setTextureFromFile(const std::string &fname) throw(int);		
		virtual bool setTexture(GLuint t, int width, int height);
		
		// get functions
		virtual GLuint getTexture();		
	};

}

#endif /*RASTERABLE_H_*/

