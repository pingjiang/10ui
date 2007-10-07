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

namespace TenUI {

	class TMMUI_TestApp : public ITenMilManUIApp {
		
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			TMMUI_TestApp(){}
			virtual ~TMMUI_TestApp(){}		

		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			void initRectangleTest();
			void initLineTest();		
			void initRasterTest();		
			void initTextTest();

		/***************************************/
		/**** ItenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void init() throw(int);
			virtual void update_preframe() throw(APPEXCEPTIONS) {}
			virtual void update_frame() throw(APPEXCEPTIONS) {}
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()							{ return "TMMUI_TestApp"; }
					
			virtual int getScreenWidth()					{ return 1280; }
			virtual int getScreenHeight()					{ return 1024; }
			virtual int getScreenBPP()						{ return 32; }
			virtual TenUI::SCREEN_OPTION getScreenOptions()	{return TenUI::WINDOWED;}
			
			virtual UserInput* getUserInput()				{ return SDLMouseInput::createInstance(); }
			
			virtual string getFontDirectory()				{return "TestResources/FontTest";}		
	};
	
}

#endif /*TMMUI_TESTAPP_H_*/
