#ifndef FONTFAMILYDATA_H_
#define FONTFAMILYDATA_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include <TenMilManUI/Graphics/Util/Utils.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

namespace TenUI {
	
	class FontFamilyData {
	public:
		enum FontFamilyData_Exception { FT2_EXCEPTION, FONT_FILE_EXCEPTION, FONTFILE_FONTFAMILY_MISMATCH, FONTSTYLE_ALREADY_EXISTS };
		enum FontFamily_Style { DEFAULT, BOLD, ITALIC, BOLD_ITALIC, UNSUPPORTED };
		
		string fontFamily;
		unsigned int h;					///< Holds the height of the font family.
		
		GLuint *defaultTextures; 	///< Holds the texture id's
		GLuint defaultListBase;  	///< Holds the texture id's
	
		GLuint *boldTextures;		///< Holds the texture id's 
		GLuint boldListBase;		///< Holds the first display list id
		
		GLuint *italicTextures;		///< Holds the texture id's 
		GLuint italicListBase;		///< Holds the first display list id
		
		GLuint *boldItalicTextures;	///< Holds the texture id's 
		GLuint boldItalicListBase;	///< Holds the first display list id	
			
	public:
		FontFamilyData(const string &famName, unsigned int height);
		virtual ~FontFamilyData();
		
		static string getFontFile_FamilyName(const string& fontFile) throw(FontFamilyData::FontFamilyData_Exception);
		static FontFamily_Style getFontFile_Style(const string& fontFile) throw(FontFamilyData::FontFamilyData_Exception);
	
		GLuint getStyleListBase(FontFamily_Style style);
		
		void render(FontFamilyData::FontFamily_Style style, int fontSize, const char *start_line){
				vector<string> lines;
	
				GLuint list_base= getStyleListBase(style); 
				
				const char * c = start_line;
				for(;*c;c++) {
					if(*c=='\n') {
						string line;
						for(const char *n=start_line;n<c;n++) line.append(1,*n);
						lines.push_back(line);
						start_line=c+1;
					}
				}
				if(start_line) {
					string line;
					for(const char *n=start_line;n<c;n++) line.append(1,*n);
					lines.push_back(line);
				}
				

				glEnable(GL_TEXTURE_2D);
				
				glListBase(list_base);
	
				for(unsigned int i=0;i<lines.size();i++) {
					glPushMatrix();
					
					GLfloat scale = ((float)fontSize)/((float)h);
					glScalef(scale, scale, 1.0);
					
				//  The commented out raster position stuff can be useful if you need to
				//  know the length of the text that you are creating.
				//  If you decide to use it make sure to also uncomment the glBitmap command
				//  in make_dlist().
				//	glRasterPos2f(0,0);
					glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
				//	float rpos[4];
				//	glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
				//	float len=x-rpos[0];
	
					glPopMatrix();
				}
				
				glDisable(GL_TEXTURE_2D);
	
		}
		
		void loadFontFile(const string &fontFile) throw(FontFamilyData::FontFamilyData_Exception) {
			if( fontFamily != getFontFile_FamilyName(fontFile) ){ throw FONTFILE_FONTFAMILY_MISMATCH; }
			else{
				if( hasStyle(getFontFile_Style(fontFile)) ){ throw FONTSTYLE_ALREADY_EXISTS;}
				else{ loadFont(fontFile); }
			}
		}
		
		bool hasStyle(FontFamily_Style style){
			switch(style){
			case DEFAULT:
				return (defaultTextures != NULL);
			case BOLD:
				return (boldTextures != NULL);
			case ITALIC:
				return (italicTextures != NULL);
			case BOLD_ITALIC:
				return (boldItalicTextures != NULL);
			case UNSUPPORTED:
				return false;
			}
			return false;
		}
		
	private: 
		void make_dlist ( FT_Face face, char ch, GLuint list_base, GLuint * tex_base );
		void loadFont(const string &fontFile) throw(int);
	};
	
}

#endif /*FONTFAMILYDATA_H_*/
