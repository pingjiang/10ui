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
#include <tr1/memory>

#include "TenMilManUI_Enums.h"
#include "ITenMilManUIApp.h"
#include "Graphics/Font/FontManager_FT2.h"
#include "UI/Core/DisplayObjectContainer.h"
#include "UI/Core/UIComponent.h"
#include "UserInputs/UserInput.h"
#include <TenMilManUI/UI/Managers/InputManager.h>


#define IMPLEMENT_TENUI_APP( tenuiApp ) int main(void) {																			\
											TenUI::ITenMilManUIApp* app = (TenUI::ITenMilManUIApp*) new TenUI::tenuiApp;			\
											TenUI::TenMilManUI* tui = TenUI::TenMilManUI::createInstance(app);						\
											tui->run();																				\
											return 0;																				\
									  }

using namespace std;
using std::tr1::shared_ptr;

namespace TenUI{
	class ITenMilManUIApp;
}

namespace TenUI {	

	class TenMilManUI {		
		
		// Private Variables
		private:
		    static TenMilManUI* inst;
		    int screenWidth;
		    int screenHeight;
		    int screenBPP;
		    //UserInput* userInput;
		    //DragManager* drgMgr;
		
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
			
			void initSDL();
			void initOpenGL();
			void initFontManager();
			
			void update(); 
			void draw();
			bool isRunning();
		

		// Public Methods
		public:
			static TenMilManUI* createInstance(ITenMilManUIApp *) throw(int);
			static TenMilManUI* instance();			

			int getScreenHeight(){ return screenHeight; }
			int getScreenWidth(){ return screenWidth; }
			
			void run() throw(int);
			void quit() throw(int);
			
			void addDisplayObject(DisplayObject *obj){
				obj->init();
				rootObjs.insert(make_pair(obj->getObjectID(), obj));
			}
			
	};

}

TenUI::TenMilManUI* getTenUI();
shared_ptr<TenUI::InputManager> getTenUIInputManager();
//TenUI::InputManager* getTenUIInputManager();

#endif /*TENMILMANUI_H_*/
