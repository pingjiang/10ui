#ifndef TENUI_TESTAPP_H_
#define TENUI_TESTAPP_H_


#include <iostream>
#include <string>

#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>


using namespace std;

namespace TenUI {

	class TenUI_TestApp : public ITenMilManUIApp {
		
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			TenUI_TestApp(){}
			virtual ~TenUI_TestApp(){}		

		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			void initButtonTest();

		/***************************************/
		/**** ItenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void init() throw(int);
			virtual void update_preframe() throw(APPEXCEPTIONS) {}
			virtual void update_frame() throw(APPEXCEPTIONS) {}
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()								{ return "TenUI_TestApp"; }
			
			virtual GraphicsOptions* getGraphicsOptions() { return new GraphicsOptions(	1280, 1024, 32, 
																	  				 		IGraphicsEnums::WINDOWED, 
																	  				 		string("resources/fonts")); 		}
			virtual IGraphics* getGraphics()					{ return OpenGL_Graphics::instance(); }
			
			virtual UserInput* getUserInput()					{ return SDLMouseInput::instance(); }
	};
	
}

#endif /*TENUI_TESTAPP_H_*/
