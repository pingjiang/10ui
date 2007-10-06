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
#include <string>
#include <map>

#include "TenMilManUI_Enums.h"
#include "UserInputs/UserInput.h"
#include "ITenMilManUIApp.h"
#include "UI/Core/DisplayObjectContainer.h"
#include "UI/Core/UIComponent.h"

#define TenUI TenMilManUI::instance()

using namespace TenMilManUI_CORE_UI_Core;
using namespace std;

namespace TenMilManUI_APP{
	class ITenMilManUIApp;
}

namespace TenMilManUI_CORE {	

	class TenMilManUI {		
		private:
		    static TenMilManUI* inst;
		    int screenWidth;
		    int screenHeight;
		    int screenBPP;
		    UserInput* userInput;
		    
		    map<long ,DisplayObject*> rootObjs;		    
		    TenMilManUI_APP::ITenMilManUIApp *app;
						
			// Indicates whether UI should continue running
			// Made for Multi-Threading
		    pthread_mutex_t runningMutex;
			bool running;
					
			TenMilManUI(TenMilManUI_APP::ITenMilManUIApp *) throw(int);						
			virtual ~TenMilManUI();
			
			void initSDL();
			void initOpenGL();
			void initFontManager();
			
			void update(); 
			void draw();
			bool isRunning();
					
		public:
			static TenMilManUI* createInstance(TenMilManUI_APP::ITenMilManUIApp *) throw(int);
			static TenMilManUI* instance();			
			
			void run() throw(int);
			void quit() throw(int);
			
			void addDisplayObject(DisplayObject *obj){
				obj->init();
				rootObjs.insert(make_pair(obj->getObjectID(), obj));
			}
			
	};

}

#endif /*TENMILMANUI_H_*/
