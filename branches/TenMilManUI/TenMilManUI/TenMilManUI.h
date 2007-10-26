#ifndef TENMILMANUI_H_
#define TENMILMANUI_H_

// includes
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <SDL.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <TenMilManUI/Graphics/IGraphics.h>
#include <TenMilManUI/Graphics/GraphicsOptions.h>
#include <TenMilManUI/ITenMilManUIApp.h>
#include <TenMilManUI/TenMilManUI_Enums.h>
#include <TenMilManUI/UI/Core/DisplayObject.h>
#include <TenMilManUI/UI/Core/DisplayObjectContainer.h>
#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UserInputs/UserInput.h>
#include "UserInputs/InputManager.h"

#define IMPLEMENT_TENUI_APP( tenuiApp ) int main(void) {																			\
											TenUI::ITenMilManUIApp* app = (TenUI::ITenMilManUIApp*) new TenUI::tenuiApp;			\
											TenUI::TenMilManUI* tui = TenUI::TenMilManUI::createInstance(app);						\
											tui->run();																				\
											return 0;																				\
									  }

using namespace std;

namespace TenUI {

	class ITenMilManUIApp;
	
	class TenMilManUI {		
		
		// Private Variables
		private:
		    static TenMilManUI* inst;
		    IGraphics* graphics;
		    UserInput* userInput;
		    
		    map<long ,DisplayObject*> rootObjs;
		    ITenMilManUIApp *app;
						
			// Indicates whether UI should continue running
			// Made for Multi-Threading
		    pthread_mutex_t runningMutex;
			bool running;

		// Private Methods
		private:
			TenMilManUI(ITenMilManUIApp *) throw(int);						
			virtual ~TenMilManUI();
						
			void update(); 
			void draw();
			bool isRunning();	

		// Public Methods
		public:
			static TenMilManUI* createInstance(ITenMilManUIApp *) throw(int);
			static TenMilManUI* instance();			
			
			void run() throw(int);
			void quit() throw(int);

			IGraphics* getGraphics(){ return graphics; }
			GraphicsOptions& getGraphicsOptions() const{
				return graphics->getGraphicsOptions();
			}			
			vector<DisplayObject *> *getUIComponentsAt(int x, int y);
			
			void addDisplayObject(DisplayObject *obj);
			
	};

}

#endif /*TENMILMANUI_H_*/
