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
		
	    pthread_mutex_init(&runningMutex,NULL);	
		running = true;
		runSelectionRendering = true;
	}	
	TenMilManUI::~TenMilManUI(){}
	
	/**********************************
	 * 	 		Public Methods	  	  *	 
	 **********************************/	
	void TenMilManUI::run() throw(int){		
		graphics->init(app->getGraphicsOptions());
		
		app->initInput();
		app->init();
		
		while(isRunning() && !InputManager::instance()->isQuit()){
			app->update_preframe();
			app->update_frame();
			
			update();
			draw();
			
			InputManager::instance()->update();
			runSelectionRendering = true;
		}
		
		app->deinit();		
		graphics->deinit();
	}

	void TenMilManUI::quit() throw(int){
		pthread_mutex_lock(&runningMutex);
		running = false;
		pthread_mutex_unlock(&runningMutex);
		
	}
	shared_ptr<UIComponent> TenMilManUI::getUIComponentsAt(int x, int y){
		if( runSelectionRendering ){
			vector<shared_ptr<DisplayObject> >::iterator it = rootObjs.begin();
			
			graphics->beginRendering(IGraphicsEnums::SELECTION);
			while(it != rootObjs.end()){
				//graphics->setColorID((*it)->getObjectID());
				(*it)->preDraw();
				(*it)->draw();
				(*it)->postDraw();
				++it;
			}
			graphics->endRendering();
			
			runSelectionRendering = false;
		}
		
		return allUIComps[graphics->getColorID(x,y)];
	}
	
	shared_ptr<UIComponent> TenMilManUI::getUIComponent(unsigned long uicompid){
		map<unsigned long , shared_ptr<UIComponent> >::iterator it = allUIComps.find(uicompid);
		return ( it != allUIComps.end() ) ? it->second : shared_ptr<UIComponent>(); 
	}
	

	void TenMilManUI::bringUIComponentFront(const shared_ptr<UIComponent>& uicomp){
		bringUIComponentFront(uicomp->getObjectID());
	}
	void TenMilManUI::bringUIComponentFront(unsigned long uicompid){
		vector< shared_ptr<DisplayObject> >::iterator it = rootObjs.begin();
		
		vector< shared_ptr<DisplayObject> >::iterator rootObjit = rootObjs.end(); 
		while(it != rootObjs.end()){
			if( (*it)->getObjectID() == uicompid ){
				rootObjit = it;
				break;
			}
			++it;
		}
		
		if(it != rootObjs.end()){
			shared_ptr<DisplayObject> rootObj = (*rootObjit);
			rootObjs.erase(rootObjit);
			rootObjs.push_back(rootObj);
		}
	}
	
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/		
	void TenMilManUI::draw(){
		vector< shared_ptr<DisplayObject> >::iterator it = rootObjs.begin();
		
		graphics->beginRendering(IGraphicsEnums::DISPLAY);
		
		while(it != rootObjs.end()){
			(*it)->preDraw();
			(*it)->draw();
			(*it)->postDraw();
			++it;
		}
		
		graphics->endRendering();			
	}
	void TenMilManUI::update(){
		vector< shared_ptr<DisplayObject> >::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){			
			(*it)->update();
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
		
	void TenMilManUI::addUIComponent(const shared_ptr<UIComponent>& uicomp){
		map<unsigned long , shared_ptr<UIComponent> >::iterator it = allUIComps.find(uicomp->getObjectID());
		if( it == allUIComps.end() ){
			rootObjs.insert(rootObjs.begin(), uicomp);
			addUIComponent_Recursive(uicomp);	
		}		
	}
	
	void TenMilManUI::addUIComponent_Recursive(const shared_ptr<UIComponent>& uicomp){
		uicomp->init();
		allUIComps[uicomp->getObjectID()] = uicomp;
		
		vector< shared_ptr<DisplayObject> >::const_iterator end = uicomp->getChildren().end();
		vector< shared_ptr<DisplayObject> >::const_iterator it = uicomp->getChildren().begin();
		while(it != end){
			shared_ptr<UIComponent> child = dynamic_pointer_cast<UIComponent>(*it);
			if(child != NULL){
				addUIComponent_Recursive(child);
			}
			++it;
		}
	}
	
}

