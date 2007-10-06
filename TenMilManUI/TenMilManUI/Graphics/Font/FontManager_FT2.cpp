#include "FontManager_FT2.h"

FontManager_FT2* FontManager_FT2::instance = NULL;

///Much like Nehe's glPrint function, but modified to work
///with freetype fonts.
void FontManager_FT2::render(const string &fontkey, FontFamilyData::FontFamily_Style style, int fontSize, const char *fmt, ...)  {
	// We want a coordinate system where things coresponding to window pixels.
	//pushScreenCoordinateMatrix();					
	
	
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		*text=0;											// Do Nothing

	else {
	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text
	}

	FontFamilyData *ft_font = fontmap[fontkey];		
	ft_font->render(style,fontSize,text);

}
