#ifndef FONTDATA_H_
#define FONTDATA_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string>
#include <stdexcept>

#include "../Util/Utils.h"

using std::vector;
using std::string;

class FontData {
public:
	enum FontData_Exceptions { FT2_EXCEPTION, FONT_FILE_EXCEPTION };
	
	float h;			///< Holds the height of the font.
	GLuint * textures;	///< Holds the texture id's 
	GLuint list_base;	///< Holds the first display list id
		
public:
	FontData(const char * fname, unsigned int h) throw(int);
	virtual ~FontData();

private: 
	void make_dlist( FT_Face, char, GLuint, GLuint *);
};

#endif /*FONTDATA_H_*/
