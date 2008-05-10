#include "OpenGL_Image.h"

namespace TenUI{
	// load images and converts them into OpenGL textures	
	sp<OpenGL_Image> OpenGL_Image::loadFromFile(const string& file) throw(OpenGL_Image_enums::Exceptions) {
		unsigned int imgw = 0;
		unsigned int imgh = 0;
		unsigned int texw = 0;
		unsigned int texh = 0;
		
		Uint8 *rowhi, *rowlo;
		Uint8 *rowhi2, *rowlo2;
		Uint8 *tmpbuf;
		SDL_Surface *image;
		int i, j;

		image = IMG_Load(file.c_str());
		if(!image){
			return sp<OpenGL_Image>();
		}
		SDL_Surface *tempimg = SDL_DisplayFormatAlpha(image);
		SDL_FreeSurface(image);
		image = tempimg;
				
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

		imgw = image->w;
		imgh = image->h;
		texw = nextPowerOfTwo(image->w);
		texh = nextPowerOfTwo(image->h);
		
		SDL_Surface *dest = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, texw, texh, 32, rmask, gmask, bmask, amask);
		SDL_SetAlpha  (dest, SDL_SRCALPHA , 0);

		if ( image == NULL ) {
			throw OpenGL_Image_enums::IMAGE_LOAD_FAILED;
			return sp<OpenGL_Image>();
		}

		// gl surfaces are upsidedown and rgb
		tmpbuf = (Uint8 *)malloc(dest->pitch);
		if ( tmpbuf == NULL ) {
			fprintf(stderr, "Out of memory\n");
			return sp<OpenGL_Image>();
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
		
		// create texture
		GLuint texid = 0;
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);   // 2d texture (x and y size)

			//TODO remove glTexParameter's from OpenGL_Image
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	
			glTexImage2D(GL_TEXTURE_2D, 0, 4, dest->w, dest->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dest->pixels);
			SDL_FreeSurface(dest);
		
		glBindTexture(GL_TEXTURE_2D, 0);   // 2d texture (x and y size)
		
		return sp<OpenGL_Image>(new OpenGL_Image(imgw, imgh, texid, texw, texh));
	}
		
	OpenGL_Image::~OpenGL_Image(){	freeTexture();	}		
	void OpenGL_Image::freeTexture(){	glDeleteTextures( 1, &texid );	}
}
