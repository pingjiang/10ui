#ifndef TMMUI_TESTAPP_H_
#define TMMUI_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>
#include <TenMilManUI/UserInputs/TableInput.h>
#include <TenMilManUI/Graphics/Vector/Rectangle.h>
#include <TenMilManUI/Graphics/Vector/Line.h>
#include <TenMilManUI/Graphics/Text/Text.h>
#include <TenMilManUI/Graphics/Raster/Rasterable.h>
#include <TenMilManUI/Graphics/Font/FontManager_FT2.h>

#include <TenMilManUI/UI/Controls/InteractiveRectangle.h>
#include <TenMilManUI/UI/Managers/SelectManager.h>

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
			void initInteractiveRectangleTest();
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
			virtual void update_frame() throw(APPEXCEPTIONS);// {}
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()							{ return "TMMUI_TestApp"; }
					
			virtual int getScreenWidth()					{ return 640; }
			virtual int getScreenHeight()					{ return 480; }
			virtual int getScreenBPP()						{ return 32; }
			virtual TenUI::SCREEN_OPTION getScreenOptions()	{return TenUI::WINDOWED;}
			
			//TODO: enable multiple UserInputs here
			//virtual UserInput* getUserInput()				{ return TableInput::createInstance(); }
			//virtual UserInput* getUserInput()				{ return SDLMouseInput::createInstance(); }
			virtual void initializeUserInput(){//				{ cout << "Tbl:\t" << TableInput::createInstance() << "\n"; cout << "SDL:\t" << SDLMouseInput::createInstance() << "\n"; }
				UserInput* tbInput = TableInput::createInstance(0);
				//UserInput* tbInput2 = TableInput::createInstance(1);
				UserInput* mInput = SDLMouseInput::createInstance();
				cout << "Tbl:\t" << tbInput << "\n";
				cout << "\tData format: " << tbInput->getDataFormat() << "\n";
				cout << "\t    UI type: " << tbInput->getType() << "\n";
				/*cout << "Tbl:\t" << tbInput2 << "\n";
				cout << "\tData format: " << tbInput2->getDataFormat() << "\n";
				cout << "\t    UI type: " << tbInput2->getType() << "\n";*/
				cout << "SDL:\t" << mInput << "\n";
				cout << "\tData format: " << mInput->getDataFormat() << "\n";
				cout << "\t    UI type: " << mInput->getType() << "\n";
			}
			virtual string getFontDirectory()				{return "TestResources/FontTest";}
			
			SelectManager* sltMgr;
	};
	
}

#endif /*TMMUI_TESTAPP_H_*/
