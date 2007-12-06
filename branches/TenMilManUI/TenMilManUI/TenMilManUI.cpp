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
		this->graphics = app->getGraphics();
		this->userInput = app->getUserInput();
		
	    pthread_mutex_init(&runningMutex,NULL);	
		running = true;
		runSelectionRendering = true;
	}	
	TenMilManUI::~TenMilManUI(){
		map<unsigned long,DisplayObject*>::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){
			it->second->deinit();
			delete (it->second);
			++it;
		}
	}
	
	/**********************************
	 * 	 		Public Methods	  	  *	 
	 **********************************/	
	void TenMilManUI::run() throw(int){		
		graphics->init(app->getGraphicsOptions());
		app->init();
						
		userInput->update();

		while(isRunning() && !userInput->isQuit()){
			app->update_preframe();
			app->update_frame();
			
			update();
			draw();

			runSelectionRendering = true;
			
			userInput->update();
		}
		
		app->deinit();		
		graphics->deinit();
	}

	void TenMilManUI::quit() throw(int){
		pthread_mutex_lock(&runningMutex);
		running = false;
		pthread_mutex_unlock(&runningMutex);
		
	}
	UIComponent* TenMilManUI::getUIComponentsAt(int x, int y){
		if( runSelectionRendering ){
			map<unsigned long,DisplayObject*>::iterator it = rootObjs.begin();
			
			graphics->beginRendering(IGraphicsEnums::SELECTION);
			while(it != rootObjs.end()){
				graphics->setColorID((it->second)->getObjectID());
				(it->second)->preDraw();
				(it->second)->draw();
				(it->second)->postDraw();
				++it;
			}
			graphics->endRendering();
			
			runSelectionRendering = true;
		}
		return allUIComps[graphics->getColorID(x,y)];
	}
	
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/		
	void TenMilManUI::draw(){
		map<unsigned long,DisplayObject*>::iterator it = rootObjs.begin();
		
		graphics->beginRendering(IGraphicsEnums::DISPLAY);
		
		while(it != rootObjs.end()){
			(it->second)->preDraw();
			(it->second)->draw();
			(it->second)->postDraw();
			++it;
		}
		
		graphics->endRendering();			
	}
	void TenMilManUI::update(){
		map<unsigned long,DisplayObject*>::iterator it = rootObjs.begin();
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
		
	void TenMilManUI::addUIComponent(UIComponent* uicomp){
		uicomp->init();
		allUIComps[uicomp->getObjectID()] = uicomp;
		rootObjs[uicomp->getObjectID()] = uicomp;
		
		vector<DisplayObject*>::iterator end = uicomp->getChildren()->end();
		vector<DisplayObject*>::iterator it = uicomp->getChildren()->begin();
		while(it != end){
			UIComponent* child = dynamic_cast<UIComponent*>(*it);
			if(child != NULL){
				addUIComponent(child);
			}
			++it;
		}		
	}
				
	
}

