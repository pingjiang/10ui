#ifndef TMMUI_TESTAPP_H_
#define TMMUI_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>
#include <TenMilManUI/Graphics/Vector/Rectangle.h>
#include <TenMilManUI/Graphics/Vector/Line.h>
#include <TenMilManUI/Graphics/Text/Text.h>
#include <TenMilManUI/Graphics/Raster/Rasterable.h>
#include <TenMilManUI/Graphics/Font/FontManager_FT2.h>

using namespace std;
using namespace TenMilManUI_CORE_Graphics_Vector;
using namespace TenMilManUI_CORE_Graphics_Raster;
using namespace TenMilManUI_CORE_Graphics_Text;
using namespace TenMilManUI_CORE;

namespace TenMilManUI_APP {
	class TMMUI_TestApp : public ITenMilManUIApp
	{
	public:
		TMMUI_TestApp(){}
		virtual ~TMMUI_TestApp(){}

		void initRectangleTest();
		void initLineTest();		
		void initRasterTest();		
		void initTextTest();
		
		virtual void init() throw(int);
		virtual void update_preframe() throw(int) {
			
		}
		virtual void update_frame() throw(int) {
			
		}
		virtual void deinit() throw(int) {
			
		}
		
		virtual char* getName(){ return "TMMUI_TestApp"; }
		
		
		virtual int getScreenWidth(){ return 1280; }
		virtual int getScreenHeight(){ return 1024; }
		virtual int getScreenBPP(){ return 32; }
		virtual TenMilManUI_CORE::SCREEN_OPTION getScreenOptions(){return TenMilManUI_CORE::FULLSCREEN;}
		virtual UserInput* getUserInput(){
			return SDLMouseInput::createInstance();
		}
	};
}

#endif /*TMMUI_TESTAPP_H_*/
