#ifndef GRAPHICSOPTIONS_H_
#define GRAPHICSOPTIONS_H_

#include <string>
#include "IGraphics_Enums.h"

#include <iostream>

namespace TenUI{

	class GraphicsOptions {
	private:
		unsigned int width;
		unsigned int height;
		unsigned int BPP;
		IGraphicsEnums::IGRAPHICS_SCREEN_MODE mode;
		std::string fontDir;
				
	public:
		GraphicsOptions(unsigned int width, unsigned int height, unsigned int BPP, IGraphicsEnums::IGRAPHICS_SCREEN_MODE mode, std::string fontDir){
			this->width = width;
			this->height = height;
			this->BPP = BPP;
			this->mode = mode;
			this->fontDir = std::string(fontDir); 
		}

		unsigned int getWidth() { return width; }
		unsigned int getHeight() { return height; }
		unsigned int getBPP()  { return BPP; }
		IGraphicsEnums::IGRAPHICS_SCREEN_MODE getScreenMode() { return mode; }
		string getFontsDirectory() { return fontDir; }
	};

}

#endif /*GRAPHICSOPTIONS_H_*/