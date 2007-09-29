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
#include "UserInputs/UserInput.h"
#include "ITenMilManUIApp.h"

namespace TenMilManUI {
	enum SCREEN_OPTION { FULLSCREEN, WINDOWED };
	enum UIEXCEPTIONS { UIEXCEPTION_SDL_INIT_FAILED, UIEXCEPTION_OPENGL_INIT_FAILED };
	
	class TenMilManUI {
		public:
			static TenMilManUI* createInstance(int ,int ,int ,SCREEN_OPTION ,UserInput *) throw(int);
			static TenMilManUI* instance();			
			
			void registerApplication(ITenMilManUIApp *app) throw(int);
			void run() throw(int);
			void quit() throw(int);		
			
		private:
		    static TenMilManUI* inst;
			ITenMilManUIApp *app;
			

			// Indicates whether UI should continue running
			// Made for Multi-Threading
		    pthread_mutex_t runningMutex;
			bool running;
			
			TenMilManUI(int,int,int,SCREEN_OPTION,UserInput *) throw(int);			
			virtual ~TenMilManUI();
			
			void draw();
			bool isRunning();
	};

}

#endif /*TENMILMANUI_H_*/
