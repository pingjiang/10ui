#ifndef IGRAPHICS_H_
#define IGRAPHICS_H_

#include <string>

#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include <TenMilManUI/Graphics/Util/Utils.h>

#include "GraphicsOptions.h"
#include "IGraphics_Enums.h"
#include "IImage.h"

using namespace std;

namespace TenUI{
	
	class IGraphics {
	public:
		virtual ~IGraphics(){}
		
		virtual void init(GraphicsOptions* graphicsOptions) throw(IGraphicsEnums::IGRAPHICS_EXCEPTION) = 0;
		virtual void deinit() = 0;
		virtual string getImplName() = 0;
		
		virtual GraphicsOptions& getGraphicsOptions() = 0;
		
		/******************************/
		/*       Viewport Methods     */
		/******************************/ 
		virtual void pushViewTransformation(int x, int y, float rotation, float scalex, float scaley) = 0;
		virtual void popViewTransformation() = 0;
				
		virtual void setClipping(int x, int y, int width, int height) = 0;
		virtual void resetClipping() = 0;				
		virtual Rect getClipping() = 0;
		
		/*******************************/
		/*      Rendering Methods      */
		/*******************************/
		virtual void beginRendering(IGraphicsEnums::IGRAPHICS_RENDERING_MODE mode) = 0;
		virtual void endRendering() = 0;
		virtual IGraphicsEnums::IGRAPHICS_RENDERING_MODE getRenderingMode() = 0;
		
		/*******************************/
		/* Selection Rendering Methods */
		/*******************************/
		virtual void setColorID(unsigned long id) = 0;
		virtual unsigned long getColorID(int x, int y) = 0;		
														
		/******************************/
		/*    Geometry Draw Methods   */
		/******************************/ 
		virtual void drawLine(int x1, int y1, int x2, int y2, int strokeSize, const ColorHex& color) = 0;		

			/******************************/
			/*   Rectangle Draw Methods   */
			/******************************/
			virtual void drawRectangle(	int x, int y, 
										int width, int height, 
										const ColorHex& color, 
										int strokeSize=0, const ColorHex& strokeColor=ColorHex::NoColor ) = 0;
			virtual void drawGradientRect(	int x, int y, 
											int width, int height, 
											const ColorHex& lb, const ColorHex& lt, const ColorHex& rt, const ColorHex& rb, 
											int strokeSize=0, const ColorHex& strokeColor=ColorHex() ) = 0;
			virtual void drawRoundedRectangle(	int x, int y, 
												int width, int height, int radius, 
												const ColorHex& color, 
												int strokeSize=0, const ColorHex& strokeColor=ColorHex() ) = 0;
			virtual void drawGradientRoundedRect(	int x, int y, 
													int width, int height, int radius, 
													const ColorHex& c1, const ColorHex& c2, const ColorHex& c3, const ColorHex& c4,
													int strokeSize=0, const ColorHex& strokeColor=ColorHex() ) = 0;
			void arcVertices(int x, int y, int radius, float a1, float a2, int resolution=10);
			
			/******************************/
			/*     Circle Draw Methods    */
			/******************************/
			virtual void drawRoundedCorner(	int x, int y, 
											double a1, double a2, 
											double radius, int resolution,
											const ColorHex& fillColor,
											int strokeSize=0, const ColorHex& strokeColor=ColorHex() ) = 0;
			
		/******************************/
		/*         Image Methods      */
		/******************************/ 
		virtual void drawImage(	const IImage* img, 
								int x, int y, 
								float opacity = 1.0,
								unsigned int width=0, unsigned int height=0) = 0;
		virtual IImage* loadImage(const string& imageFile) = 0;

		/******************************/
		/*         Text Methods       */
		/******************************/
		virtual void drawText(const string& text, const string& fontKey,int fontSize, int x, int y, const ColorHex& color) = 0;
		virtual void loadFontDir(const string &fontdir) = 0;
		
	protected:
		virtual void setColor(float red, float green, float blue, float alpha) = 0;
		virtual void setColor(const ColorHex& ch) = 0;
	};
	
}

#endif /*IGRAPHICS_H_*/
