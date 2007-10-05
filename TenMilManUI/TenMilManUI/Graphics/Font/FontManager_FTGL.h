#ifndef FONTMANAGER_FTGL_H_
#define FONTMANAGER_FTGL_H_

#include    <map>
#include    <string>
#include 	<FTFont.h>
#include    <FTGLTextureFont.h>

using namespace std;

typedef map<string, FTFont*> FontList;
typedef FontList::const_iterator FontIter;

class FontManager {
	public:
		enum FontManagerExceptions {GET_FONT_EXCEPTION,FONT_NOT_LOADED_EXCEPTION,FONT_SIZE_EXCEPTION};
    public:
        // NOTE
        // This is shown here for brevity. The implementation should be in the source
        // file otherwise your compiler may inline the function resulting in 
        // multiple instances of FTGLFontManager
        static FontManager& Instance()
        {
            static FontManager tm;
            return tm;
        }
        
        ~FontManager()
        {
            FontIter font;
            for( font = fonts.begin(); font != fonts.end(); font++){
                delete (*font).second;
            }
            fonts.clear();
        }

        
        FTFont* loadFont(string fname, string fontKey) throw(int) {
        	// Check to see if font exists in fontlist
        	FontIter result = fonts.find(fontKey);
            if( result != fonts.end()){
                return result->second;
	        }else{	        
	            // Load the font otherwise
	            FTFont* font = new FTGLTextureFont(fname.c_str());
	            
	            // Font loaded correctly
	            if( font->CharMapCount() == 0 ){
	            	throw GET_FONT_EXCEPTION;
	                delete font;
	                return NULL;
	            }        
	            
	            fonts[fontKey] = font;
            
	            return font;
	        }
        }
        
        FTFont* getFont(string fontKey, int size) throw(int){
        	FontIter result = fonts.find(fontKey);
            if( result != fonts.end()){

	            if( !result->second->FaceSize( size) ){
	            	throw FONT_SIZE_EXCEPTION;
	                return NULL;
	            }
	        
                return result->second;
	        }else{
            	throw FONT_NOT_LOADED_EXCEPTION;
	        }
        }
    
        
    private:
    	FontManager(){}
        FontManager(const FontManager&){};
        FontManager& operator = (const FontManager&){ return *this;};
        
        // container for fonts
        FontList fonts;    
};

#endif /*FONTMANAGER_FTGL_H_*/
