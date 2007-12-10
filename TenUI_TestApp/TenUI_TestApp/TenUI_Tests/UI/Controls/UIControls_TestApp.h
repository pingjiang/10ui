#ifndef UICONTROLS_TESTAPP_H_
#define UICONTROLS_TESTAPP_H_

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

	class UIControls_TestApp : public ITenMilManUIApp {
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			UIControls_TestApp(){}
			virtual ~UIControls_TestApp(){}		


		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			unsigned long prevObjID;
			
		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:

		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void initInput();
			virtual void init() throw(int);
			virtual void update_preframe() throw(APPEXCEPTIONS) {}
			virtual void update_frame() throw(APPEXCEPTIONS);
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()								{ return "UI Controls Test App"; }
			
			virtual GraphicsOptions* getGraphicsOptions() 		{ return new GraphicsOptions(	"UI Controls Test App",
																								1024, 768, 32, 
																	  				 			IGraphicsEnums::WINDOWED, 
																	  				 			string("")); 		}
			virtual IGraphics* getGraphics()					{ return OpenGL_Graphics::instance(); }
	};
	
}

#endif /*UICONTROLS_TESTAPP_H_*/
