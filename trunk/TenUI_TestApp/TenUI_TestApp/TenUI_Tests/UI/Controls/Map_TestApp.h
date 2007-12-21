#ifndef MAP_TESTAPP_H_
#define MAP_TESTAPP_H_

#include <iostream>
#include <string>

#include <TenMilManUI/ITenUIApp.h>
#include <TenMilManUI/TenUI.h>
#include <TenMilManUI/UserInputs/SDLMouseInput.h>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/OpenGL_Graphics/OpenGL_Graphics.h>
#include <TenMilManUI/UI/Controls/DraggableButton/DraggableButton.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>

using namespace std;

namespace TenUI {

	class Map_TestApp : public ITenUIApp {
		/***************************************/
		/************ Public Methods ***********/
		/***************************************/
		public:
			Map_TestApp(){}
			virtual ~Map_TestApp(){}		


		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			unsigned long prevObjID;
			
		/***************************************/
		/*********** Private Methods ***********/
		/***************************************/
		private:
			void styleUnit(bool isRed, const shared_ptr<DraggableButton>& unit, const string& unitIcon);

		/***************************************/
		/**** ITenMilManUIApp Implmentation ****/
		/***************************************/
		public:
			virtual void initInput();
			virtual void init() throw(int);
			virtual void update_preframe() throw(APPEXCEPTIONS) {}
			virtual void update_frame() throw(APPEXCEPTIONS);
			virtual void deinit() throw(APPEXCEPTIONS) {}
			
			virtual char* getName()								{ return "Map Test App"; }
			
			virtual GraphicsOptions* getGraphicsOptions() 		{ return new GraphicsOptions(	"UI Controls Test App",
																								1024, 768, 32, 
																	  				 			IGraphicsEnums::FULLSCREEN, 
																	  				 			string("")); 		}
			virtual IGraphics* getGraphics()					{ return OpenGL_Graphics::instance(); }
	};
	
}

#endif /*MAP_TESTAPP_H_*/
