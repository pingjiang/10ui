#ifndef OPENGL_GRAPHICS_H_
#define OPENGL_GRAPHICS_H_


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
#include <vector>

#include "OpenGL_Image.h"
#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include <TenMilManUI/Graphics/Util/Utils.h>

#include "Font/FontManager_FT2.h"

using namespace std;

namespace TenUI{
	
	class OpenGL_Graphics : public IGraphics{
	
	/******************************/
	/*  Singleton Implementation  */
	/******************************/ 
	private:
		static OpenGL_Graphics* inst;
		OpenGL_Graphics(){}
		
	public:
		static OpenGL_Graphics* instance();
		
	/******************************/
	/*  IGraphics Implementation  */
	/******************************/
	// Constants
	private: 
		static const float PI;
		
	// Member Variables
	private:
		GraphicsOptions*			graphicsOptions;
		FontManager_FT2*			fontMgr;
		vector<OpenGL_Image*> 		images;
		IGraphicsEnums::IGRAPHICS_RENDERING_MODE 	renderMode;
		
		GLuint redSelMask;
		GLuint greenSelMask;
		GLuint blueSelMask;
		GLuint alphaSelMask;
		
		unsigned int redSelShift;
		unsigned int greenSelShift;
		unsigned int blueSelShift;
		unsigned int alphaSelShift;
		
	// Helper Methods
	private:
		void arcVertices(int x, int y, int radius, float a1, float a2, int resolution=20);
		char *int2bin(int a);
		char *byte2bin(unsigned char a);
		
	public:
		virtual ~OpenGL_Graphics(){
			//TODO Free Images
			//TODO Unload Fonts
		}

		virtual void init(GraphicsOptions* graphicsOptions) throw(IGraphicsEnums::IGRAPHICS_EXCEPTION);
		virtual void deinit();
		virtual string getImplName();
		
		virtual GraphicsOptions& getGraphicsOptions();
		
		/******************************/
		/*       Viewport Methods     */
		/******************************/ 
		virtual void pushViewTransformation(int x, int y, float rotation, float scalex, float scaley);
		virtual void popViewTransformation();
		
		virtual void setClipping(int x, int y, int width, int height);
		virtual void resetClipping();
		virtual Rect getClipping();
										
		/*******************************/
		/*      Rendering Methods      */
		/*******************************/
		virtual void beginRendering(IGraphicsEnums::IGRAPHICS_RENDERING_MODE mode);
		virtual void endRendering();
		
		/*******************************/
		/* Selection Rendering Methods */
		/*******************************/
		virtual void setColorID(unsigned long id);
		virtual unsigned long getColorID(int x, int y);		
		
		/******************************/
		/*    Geometry Draw Methods   */
		/******************************/ 
		virtual void drawLine(int x1, int y1, int x2, int y2, int strokeSize, const ColorHex& color);		
	
			/******************************/
			/*   Rectangle Draw Methods   */
			/******************************/
			virtual void drawRectangle(	int x, int y, 
										int width, int height, 
										const ColorHex& color, 
										int strokeSize=0, const ColorHex& strokeColor=ColorHex::NoColor );
			virtual void drawGradientRect(	int x, int y, 
											int width, int height, 
											const ColorHex& lb, const ColorHex& lt, const ColorHex& rt, const ColorHex& rb, 
											int strokeSize=0, const ColorHex& strokeColor=ColorHex::NoColor );
			virtual void drawRoundedRectangle(	int x, int y, 
												int width, int height, int radius, 
												const ColorHex& color, 
												int strokeSize=0, const ColorHex& strokeColor=ColorHex::NoColor );
			virtual void drawGradientRoundedRect(	int x, int y, 
													int width, int height, int radius, 
													const ColorHex& c1, const ColorHex& c2, const ColorHex& c3, const ColorHex& c4,
													int strokeSize=0, const ColorHex& strokeColor=ColorHex::NoColor );
	
			/******************************/
			/*     Circle Draw Methods    */
			/******************************/
			virtual void drawRoundedCorner(	int x, int y, 
											double a1, double a2, 
											double radius, int resolution,
											const ColorHex& fillColor,
											int strokeSize=0, const ColorHex& strokeColor=ColorHex() );
			
		/******************************/
		/*         Image Methods      */
		/******************************/ 
		virtual void drawImage(	const IImage* img, 
								int x, int y, 
								float opacity = 1.0,
								unsigned int width=0, unsigned int height=0);
		virtual const IImage* loadImage(const string& imageFile);
	
		/******************************/
		/*         Text Methods       */
		/******************************/
		virtual void drawText(const string& text, const string& fontKey,int fontSize, int x, int y, const ColorHex& color);
		virtual void loadFontDir(const string &fontdir);
		
	protected:
		virtual void setColor(float red, float green, float blue, float alpha);
		virtual void setColor(const ColorHex& ch);
	};
	
}

#endif /*OPENGL_GRAPHICS_H_*/
