#include "TenMilManUI.h"

namespace TenUI {	

	/**********************************
	 * 	   Singleton Implementation	  *	 
	 **********************************/
	TenMilManUI* TenMilManUI::inst = 0;
	TenMilManUI* TenMilManUI::createInstance(ITenMilManUIApp *app) throw(int){
		if(TenMilManUI::inst == 0){
			TenMilManUI::inst = new TenMilManUI(app);
		}
		return TenMilManUI::inst;
	}
	TenMilManUI* TenMilManUI::instance(){
		return TenMilManUI::inst;
	}	

	/**********************************
	 * 	 	Constructor/Destructor	  *	 
	 **********************************/
	TenMilManUI::TenMilManUI(ITenMilManUIApp *app) throw(int)	{
		this->app = app;
		screenWidth = app->getScreenWidth();		
		screenHeight = app->getScreenHeight();
		screenBPP = app->getScreenBPP();
		userInput = app->getUserInput();
		
		running = true;
	    pthread_mutex_init(&runningMutex,NULL);	
	    	    
	    
	    initSDL();
	    initOpenGL();

	    initFontManager();
	}	
	TenMilManUI::~TenMilManUI(){
		map<long,DisplayObject*>::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){
			delete (it->second);
			++it;
		}
	}
	
	/**********************************
	 * 	 		Public Methods	  	  *	 
	 **********************************/	
	void TenMilManUI::run() throw(int){
		userInput->update();
		
		app->init();
		
		while(isRunning() && !userInput->isQuit()){			
			app->update_preframe();
			app->update_frame();
			update();
			draw();

			userInput->update();
		}
		app->deinit();
		SDL_Quit();
	}
		
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/
	void TenMilManUI::initSDL(){
		// initialize sdl video
		if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
			throw UIEXCEPTION_SDL_INIT_FAILED;
			return;
		}
		if ( SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_OPENGL | ((app->getScreenOptions() == FULLSCREEN)?SDL_FULLSCREEN:0) ) == NULL ) { 
			SDL_Quit();
			throw UIEXCEPTION_SDL_INIT_FAILED;
			return;
		}

		SDL_WM_SetCaption(app->getName(), NULL);
	}
	
	void TenMilManUI::initOpenGL(){		
		// initialize OpenGL
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations		

		glEnable(GL_BLEND);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0);					// Full Brightness.  50% Alpha
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);	// Set The Blending Function For Translucency	
		
		glEnable (GL_LINE_SMOOTH);
	}
	
	void TenMilManUI::initFontManager(){
		FontManager_FT2::createInstance(app->getFontDirectory());
	}
	
	void TenMilManUI::draw(){
		map<long,DisplayObject*>::iterator it = rootObjs.begin();
		int vPort[4];

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glGetIntegerv(GL_VIEWPORT, vPort);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		
		glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		   
		while(it != rootObjs.end()){
			(it->second)->preDraw();
			(it->second)->draw();
			(it->second)->postDraw();
			++it;
		}
		
		SDL_GL_SwapBuffers();
		
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();   
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();	
	}
	void TenMilManUI::update(){
		map<long,DisplayObject*>::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){
			(it->second)->update();
			++it;
		}
	}
	
	bool TenMilManUI::isRunning(){
		bool temp;
		pthread_mutex_lock(&runningMutex);
		temp = running;
		pthread_mutex_unlock(&runningMutex);
		return temp;
	}
	
}


TenUI::TenMilManUI* getTenUI(){ return TenUI::TenMilManUI::instance(); }
