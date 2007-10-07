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
		
		SDL_Surface *LoadTextureFromFile(const char *filename)
		{
			Uint8 *rowhi, *rowlo;
			Uint8 *rowhi2, *rowlo2;
			Uint8 *tmpbuf;
			SDL_Surface *image;
			int i, j;
	
			image = IMG_Load(filename);
			if(!image){
				return 0;
			}
			SDL_Surface *tempimg = SDL_DisplayFormatAlpha(image);
			SDL_FreeSurface(image);
			image = tempimg;
			setW(image->w);
			setH(image->h);
			
			//TODO What the Fuck is this?
			setX(getX());
			setY(getY());
			
			SDL_SetAlpha  (image, SDL_SRCALPHA , 0);
	
			Uint32 rmask, gmask, bmask, amask;
	
			#if SDL_BYTEORDER == SDL_BIG_ENDIAN
				rmask = 0xff000000;
				gmask = 0x00ff0000;
				bmask = 0x0000ff00;
				amask = 0x000000ff;
			#else
				rmask = 0x000000ff;
				gmask = 0x0000ff00;
				bmask = 0x00ff0000;
				amask = 0xff000000;
			#endif		
	
			this->texw = (int) pow(2.0,((int) ceil( log((double)image->w)/log(2.0) )));
			this->texh =(int) pow(2.0,((int) ceil( log((double)image->h)/log(2.0) )));
			
			SDL_Surface *dest = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, texw, texh, 32, rmask, gmask, bmask, amask);
			SDL_SetAlpha  (dest, SDL_SRCALPHA , 0);
	
			if ( image == NULL ) {
				fprintf(stderr, "Unable to load %s: %s\n", filename, SDL_GetError());
				return(NULL);
			}
	
			// gl surfaces are upsidedown and rgb
			tmpbuf = (Uint8 *)malloc(dest->pitch);
			if ( tmpbuf == NULL ) {
				fprintf(stderr, "Out of memory\n");
				return(NULL);
			}
			int bpp = image->format->BytesPerPixel;
			rowhi = (Uint8 *)image->pixels;
			rowlo = rowhi + (image->h * image->pitch) - image->pitch;
	
			rowhi2 = (Uint8 *)dest->pixels;
			rowlo2 = rowhi2 + ((image->h-1) * dest->pitch) - dest->pitch;
	
			for ( i=0; i<image->h/2; ++i ) {
				 for ( j=0; j<image->w; ++j ) {
					rowhi2[j*bpp] = rowhi[j*bpp+2];
					rowhi2[j*bpp+1] = rowhi[j*bpp+1];
					rowhi2[j*bpp+2] = rowhi[j*bpp];
					rowhi2[j*bpp+3] = rowhi[j*bpp+3];
	
					if( rowhi2[j*bpp] == 255 && rowhi2[j*bpp+1] == 0  && rowhi2[j*bpp+2] == 255 ){
						rowhi2[j*bpp+3] = 0;
					}			
					
					
					rowlo2[j*bpp] = rowlo[j*bpp+2];
					rowlo2[j*bpp+1] = rowlo[j*bpp+1];
					rowlo2[j*bpp+2] = rowlo[j*bpp];
					rowlo2[j*bpp+3] = rowlo[j*bpp+3];
					
					
					if( rowlo2[j*bpp] == 255 && rowlo2[j*bpp+1] == 0  && rowlo2[j*bpp+2] == 255 ){
						rowlo2[j*bpp+3] = 0;
					}
					
				}
				memcpy(tmpbuf, rowhi2, dest->pitch);
				memcpy(rowhi2, rowlo2, dest->pitch);
				memcpy(rowlo2, tmpbuf, dest->pitch);
				rowhi  += image->pitch;
				rowlo  -= image->pitch;
	
				rowhi2 += dest->pitch;
				rowlo2 -= dest->pitch;
			}
			free(tmpbuf);
			SDL_FreeSurface(image);
	
			return(dest);
		}
	
		// load bmps and convert to textures
		bool LoadGLTextures(const char *filename)
		{	
			SDL_Surface *img = LoadTextureFromFile(filename);
			if (!img) {
				return false;
			}
			// create texture	
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);   // 2d texture (x and y size)
	
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
			SDL_FreeSurface(img);
			
			return true;
		}
	
	public:
	
		// constructor
		Rasterable(DisplayObject *p, int x=0, int y=0, double r=0.0, double s=1.0, double o=1.0)
			:DisplayObject(p,x,y,r,s,o){			
			texw = -1;
			texh = -1;					
			textureSet = false;
		}	
		virtual ~Rasterable(){}
			
		// game loop (and init) function
		virtual void init(){}
		virtual void update(){}
		virtual void draw(){		
			if( textureSet ){
				glColor4d(1.0,1.0,1.0,(GLfloat)this->opacity);
		
				// bind texture to rectangle
				glBindTexture(GL_TEXTURE_2D, texture);
				
				// draw rectangle
				glBegin(GL_QUADS);		                
					glTexCoord2i(0,0); glVertex2d(left,bottom);
					glTexCoord2i(0,1); glVertex2d(left,bottom+texh);
					glTexCoord2i(1,1); glVertex2d(left+texw,bottom+texh);
					glTexCoord2i(1,0); glVertex2d(left+texw,bottom);
				glEnd();
			}
		}
		virtual void postDraw(){
			glBindTexture(GL_TEXTURE_2D, 0);
			DisplayObject::postDraw();
		}
		
		// getter/setter functions				
		// set functions
		virtual void setTextureFromFile(const std::string &fname) throw(int) {
			textureSet = LoadGLTextures(fname.c_str());
			if(!textureSet){
				throw SET_TEXTURE_FAILED;
			}
		}
		
		virtual bool setTexture(GLuint t, int width, int height){
			this->texture = t;
			setW(width);
			setH(height);
			setX(getX());
			setY(getY());
			
			texw = (int) pow(2.0,((int) ceil( log((double)w)/log(2.0) )));
			texh = (int) pow(2.0,((int) ceil( log((double)h)/log(2.0) )));
			
			return (textureSet = true);
		}
		
		// get functions
		virtual GLuint getTexture(){
			return texture;	
		}
		
	};

}

#endif /*RASTERABLE_H_*/

