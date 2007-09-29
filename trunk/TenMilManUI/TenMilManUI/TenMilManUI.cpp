#include "TenMilManUI.h"

namespace TenMilManUI {	

	/**********************************
	 * 	   Singleton Implementation	  *	 
	 **********************************/
	TenMilManUI* TenMilManUI::inst = 0;
	TenMilManUI* TenMilManUI::createInstance(int screen_width,int screen_height,int screen_bpp, SCREEN_OPTION screen_opt, UserInput *input) throw(int){
		if(TenMilManUI::inst == 0){
			TenMilManUI::inst = new TenMilManUI(screen_width,screen_height, screen_bpp, screen_opt, input);
		}
		return TenMilManUI::inst;
	}
	TenMilManUI* TenMilManUI::instance(){
		return TenMilManUI::inst;
	}	

	/**********************************
	 * 	 	Constructor/Destructor	  *	 
	 **********************************/
	TenMilManUI::TenMilManUI(int screen_width,int screen_height,int screen_bpp, SCREEN_OPTION screen_opt, UserInput *input) throw(int){
		running = false;
	    pthread_mutex_init(&runningMutex,NULL);
		
		// initialize sdl video
		if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
			throw UIEXCEPTION_SDL_INIT_FAILED;
			return;
		}
		
		if ( SDL_SetVideoMode(screen_width, screen_height, 0, SDL_OPENGL | ((screen_opt == FULLSCREEN)?SDL_FULLSCREEN:0) ) == NULL ) { 
			SDL_Quit();
			throw UIEXCEPTION_SDL_INIT_FAILED;
			return;
		}
	}	
	TenMilManUI::~TenMilManUI(){}
	
	/**********************************
	 * 	 		Public Methods	  	  *	 
	 **********************************/
	void TenMilManUI::registerApplication(ITenMilManUIApp *app) throw(int) {
		this->app = app;
		this->app->init();
	}
	
	void TenMilManUI::run() throw(int){
		while(isRunning()){
			app->update_preframe();
			app->update_frame();
			draw();
		}
		app->deinit();
	}
		
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/
	void TenMilManUI::draw(){
		
	}
	
	bool TenMilManUI::isRunning(){
		bool temp;
		pthread_mutex_lock(&runningMutex);
		temp = running;
		pthread_mutex_unlock(&runningMutex);
		return temp;
	}
	
}
