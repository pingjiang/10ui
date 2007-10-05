#ifndef FONTMANAGER_FT2_H_
#define FONTMANAGER_FT2_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

#include <cstdarg>

#include "FontData.h"

#define FontMgr FontManager_FT2::Instance()

using std::vector;
using std::string;
using std::map;

class FontManager_FT2 {
private:
	map<string, FontData*> fontmap;

	FontManager_FT2 (){}
	FontManager_FT2 (const FontManager_FT2 &){};
	FontManager_FT2& operator = (const FontManager_FT2&){ return *this;};
	
public:
	enum FontManager_Exceptions { LOAD_FONT_EXCEPTION, FONTKEY_ALREADY_EXISTS, FONTKEY_DOESNT_EXIST };
	
	// NOTE
    // This is shown here for brevity. The implementation should be in the source
    // file otherwise your compiler may inline the function resulting in 
    // multiple instances of FTGLFontManager
    static FontManager_FT2& Instance(){
        static FontManager_FT2 tm;
        return tm;
    }
	
	
	void loadFont(const string &fname, const string &fontKey) throw(int){
		if(fontmap.find(fontKey) != fontmap.end()){
			throw FONTKEY_ALREADY_EXISTS;
		}else{		
			try{
				FontData *newFont = new FontData(fname.c_str(), 16);
				fontmap[fontKey] = newFont;
			}catch(int e){
				switch(e){
				case FontData::FT2_EXCEPTION:
				case FontData::FONT_FILE_EXCEPTION:
					throw LOAD_FONT_EXCEPTION;
				}
			}
		}
	}

	//The flagship function of the library - this thing will print
	//out text at window coordinates x,y, using the font ft_font.
	//The current modelview matrix will also be applied to the text. 
	void print(const string &fontkey, float x, float y, const char *fmt, ...);
	
};

#endif /*FONTMANAGER_FT2_H_*/
