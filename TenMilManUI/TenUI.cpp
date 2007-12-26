#include "TenUI.h"

namespace TenUI {	

	/**********************************
	 * 	   Singleton Implementation	  *	 
	 **********************************/
	TenUI* TenUI::inst = 0;
	TenUI* TenUI::createInstance(ITenUIApp *app) throw(int){
		if(TenUI::inst == 0){
			TenUI::inst = new TenUI(app);
		}
		return TenUI::inst;
	}
	TenUI* TenUI::instance(){
		return TenUI::inst;
	}	

	/**********************************
	 * 	 	Constructor/Destructor	  *	 
	 **********************************/
	TenUI::TenUI(ITenUIApp *app) throw(int)	{
		this->app = app;	        
		
	    running = true;
		runSelectionRendering = true;
	}	
	TenUI::~TenUI(){}
	
	/**********************************
	 * 	 		Public Methods	  	  *	 
	 **********************************/	
	void TenUI::run(){	
		
		// Initializes Graphics
		this->graphics = app->initGraphics();
		
		// Initializes UserInputs
		app->initUserInputs();
		
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

	void TenUI::quit(){
		running = false;
		
	}
	shared_ptr<UIComponent> TenUI::getUIComponentsAt(int x, int y){
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
	
	shared_ptr<UIComponent> TenUI::getUIComponent(unsigned long uicompid){
		map<unsigned long , shared_ptr<UIComponent> >::iterator it = allUIComps.find(uicompid);
		return ( it != allUIComps.end() ) ? it->second : shared_ptr<UIComponent>(); 
	}
	

	void TenUI::bringUIComponentFront(const shared_ptr<UIComponent>& uicomp){
		bringUIComponentFront(uicomp->getObjectID());
	}
	void TenUI::bringUIComponentFront(unsigned long uicompid){
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
	void TenUI::draw(){
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
	void TenUI::update(){
		vector< shared_ptr<DisplayObject> >::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){			
			(*it)->update();
			++it;
		}
	}
	
	bool TenUI::isRunning(){
		return running;
	}
		
	void TenUI::addUIComponent(const shared_ptr<UIComponent>& uicomp){
		map<unsigned long , shared_ptr<UIComponent> >::iterator it = allUIComps.find(uicomp->getObjectID());
		if( it == allUIComps.end() ){
			rootObjs.insert(rootObjs.begin(), uicomp);
			addUIComponent_Recursive(uicomp);	
		}		
	}
	
	void TenUI::addUIComponent_Recursive(const shared_ptr<UIComponent>& uicomp){
		//uicomp->init();
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

