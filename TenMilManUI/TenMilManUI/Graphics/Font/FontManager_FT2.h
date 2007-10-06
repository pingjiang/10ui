#ifndef FONTMANAGER_FT2_H_
#define FONTMANAGER_FT2_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

#include <cstdarg>

#include "FontFamilyData.h"
#include "../../Util/FileUtils.h"

#define FontMgr FontManager_FT2::Instance()

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;

class FontManager_FT2 {
	
/// Private Variables
private:
	static FontManager_FT2* instance;
	map<string, FontFamilyData*> fontmap;
	unsigned int defFontHeight;

// Private Functions
private:
	FontManager_FT2 (const string &fontDir,unsigned int defaultFontHeight){ this->defFontHeight=defaultFontHeight; loadFontDirectory(fontDir); }
	FontManager_FT2 (const FontManager_FT2 &){};
	FontManager_FT2& operator = (const FontManager_FT2&){ return *this;};

// Public Variables
public:
	enum FontManager_Exceptions { LOAD_FONT_DIRECTORY_EXCEPTION, LOAD_FONT_EXCEPTION, FONTFAMILY_DOESNT_EXIST };

// Public Functions
public:
	// Singleton Instance Creator
    static FontManager_FT2* createInstance(const string &fontDir, unsigned int defaultFontHeight=32){
    	if(instance == NULL){
    		instance = new FontManager_FT2(fontDir, defaultFontHeight);
    	}
        return instance;
    }
    // Singleton Instance Getter
    static FontManager_FT2* Instance(){
    	return instance;
    }    

    // Loads a font given a font file (path) and registers it under a font key
	void loadFontDirectory(const string &fontDir) throw(int){
		vector<string> fontDirFiles;
		FileUtils::getDirFiles(fontDir, fontDirFiles);
		
		vector<string>::iterator fit = fontDirFiles.begin();
		while(fit != fontDirFiles.end()){
			loadFont(fontDir+"/"+(*fit));				
			++fit;
		}
	}
	
    // Loads a font given a font file (path) and registers it under a font key
	void loadFont(const string &fname){
		try{
			string famName = FontFamilyData::getFontFile_FamilyName(fname);
			if(fontmap.find(famName) != fontmap.end()){
				fontmap[famName]->loadFontFile(famName);
			}else{
				FontFamilyData *newFontFamily = new FontFamilyData(famName, this->defFontHeight);
				newFontFamily->loadFontFile(fname);
				fontmap[famName] = newFontFamily;				
			}
		}catch(FontFamilyData::FontFamilyData_Exception e){
			return;
		}
	}

	//The flagship function of the library - this thing will print
	//out text at window coordinates x,y, using the font ft_font.
	//The current modelview matrix will also be applied to the text. 
	void render(const string &fontkey, FontFamilyData::FontFamily_Style style, int fontSize, const char *fmt, ...);	
};

#endif /*FONTMANAGER_FT2_H_*/
