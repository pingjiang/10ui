#ifndef TENUI_TESTAPP_H_
#define TENUI_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenUIApp.h>
#include <TenMilManUI/TenUI.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>


using namespace std;

namespace TenUI {

	class TenUI_TestApp : public ITenUIApp {
		
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

		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void init() throw(int);
			virtual void update_preframe() throw(APPEXCEPTIONS) {}
			virtual void update_frame() throw(APPEXCEPTIONS) {}
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()								{ return "Base TenUI_TestApp"; }
			
			virtual GraphicsOptions* getGraphicsOptions() 		{ return new GraphicsOptions(	"TenUI_TestApp",
																								1024, 768, 32, 
																	  				 			IGraphicsEnums::WINDOWED, 
																	  				 			string("")); 		}
			virtual IGraphics* getGraphics()					{ return OpenGL_Graphics::instance(); }
	};
	
}

#endif /*TENUI_TESTAPP_H_*/
