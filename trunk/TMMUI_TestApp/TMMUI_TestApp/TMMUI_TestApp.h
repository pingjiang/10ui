#ifndef TMMUI_TESTAPP_H_
#define TMMUI_TESTAPP_H_

#include <iostream>

#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>
#include <TenMilManUI/Graphics/Vector/Rectangle.h>


using namespace std;
using namespace TenMilManUI_CORE_Graphics_Vector;
using namespace TenMilManUI_CORE;

namespace TenMilManUI_APP {
	class TMMUI_TestApp : public ITenMilManUIApp
	{
	public:
		TMMUI_TestApp(){}
		virtual ~TMMUI_TestApp(){}
		
		void init() throw() {			
			TenMilManUI::instance()->addDisplayObject(new Rectangle(NULL, 100, 100, 100, 100,	//x,y,w,h
																		  1.0,0.0,0.0, 			//r,g,b
																		  0.0, 1.0, 1.0, 		//stroke color
																		  1.0));				//
			TenMilManUI::instance()->addDisplayObject(new Rectangle(NULL, 100, 100, 100, 100,1.0,0.0,0.0, 0.0, 1.0, 1.0, 1.0));				
		}
		void update_preframe() throw(int) {
			
		}
		void update_frame() throw(int) {
			
		}
		void deinit() throw(int) {
			
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
