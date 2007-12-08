#ifndef OPENGL_IMAGE_H_
#define OPENGL_IMAGE_H_

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

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include <TenMilManUI/Graphics/IImage.h>
#include <TenMilManUI/Graphics/Util/Utils.h>

using namespace std;

namespace TenUI{ 
	
	namespace OpenGL_Image_enums{
		enum Exceptions { IMAGE_LOAD_FAILED };
	}

	class OpenGL_Image : public IImage {
	protected:
		unsigned int imgw;
		unsigned int imgh;
		GLuint texid;
		unsigned int texw;
		unsigned int texh;

		OpenGL_Image(unsigned int nimgw, unsigned int nimgh, GLuint ntexid, unsigned int ntexw, unsigned int ntexh):imgw(nimgw),imgh(nimgh),texid(ntexid),texw(ntexw),texh(ntexh){}
	
	public:
		// load images and converts them into OpenGL textures
		static OpenGL_Image* loadFromFile(const string& file) throw(OpenGL_Image_enums::Exceptions);
		
	public:
		virtual ~OpenGL_Image();
	
		virtual GLuint		 getTextureID()		{return texid;}
		virtual unsigned int getTextureWidth()	{return texw;}
		virtual unsigned int getTextureHeight()	{return texh;}
		virtual unsigned int getImageWidth()	{return imgw;}
		virtual unsigned int getImageHeight()	{return imgh;}
		
		virtual void freeTexture();
	};
	
}
#endif /*OPENGL_IMAGE_H_*/
