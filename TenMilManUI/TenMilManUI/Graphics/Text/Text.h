#ifndef TEXT_H_
#define TEXT_H_


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

#include <string>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "../DisplayObject.h"
#include "../Util/ColorHex.h"
#include "../Font/FontManager_FT2.h"

using namespace std;

namespace TenMilManUI_CORE_Graphics_Text {

	//@Property	Text, string, RW
	//@Style 	Font, string, RW
	//@Style 	FontSize, int, RW
	//@Style 	Color, colorhex, RW
	class Text : DisplayObject {
		string text;
		string fontKey;
		int fontSize;
		ColorHex color;
		
	public:
		Text(DisplayObject *p, int x, int y, double rot=0.0, double s=1.0, float o=1.0):DisplayObject(p,x,y,rot,s,o){
			color.setColor("#FFF");
		}		
		virtual ~Text();

		string getText() {return text;}
		void setText(const string &text){this->text = text;}
		
		string getFont() {return fontKey;}
		void setFont(const string &font){fontKey = font;}
		
		int getFontSize() {return fontSize;}
		void setFontSize(int fontSize) {this->fontSize = fontSize;}
				
		ColorHex &getColor() {return color;}
		void setColor(const string fontSize) {color.setColor(fontSize);}
		
		virtual void init(){}
		virtual void update(){}	
		virtual void draw(){
			glColor4d(color.getRed(),color.getGreen(),color.getBlue(),(GLfloat)this->opacity);
			FontMgr->render(fontKey,FontFamilyData::DEFAULT, fontSize, "%s",text.c_str());
		}
		virtual void postDraw(){
			glBindTexture(GL_TEXTURE_2D, 0);
			DisplayObject::postDraw();
		}
	};
	
}

#endif /*TEXT_H_*/
