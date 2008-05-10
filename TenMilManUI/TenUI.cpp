#include "TenUI.h"

namespace TenUI {	

	/**********************************
	 * 	   Singleton Implementation	  *	 
	 **********************************/
	TenUI* TenUI::inst = 0;
	TenUI* TenUI::createInstance(ITenUIApp *app) throw(int){
		cout << "TenUI::createInstance()" << endl;
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
	sp<UIComponent> TenUI::getUIComponentsAt(int x, int y){
		if( runSelectionRendering ){
			
			vector<sp<DisplayObject> >::iterator it = rootObjs.begin();
			
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
	
	sp<UIComponent> TenUI::getUIComponent(unsigned long uicompid){
		map<unsigned long , sp<UIComponent> >::iterator it = allUIComps.find(uicompid);
		return ( it != allUIComps.end() ) ? it->second : sp<UIComponent>(); 
	}
	

	void TenUI::bringUIComponentFront(const sp<UIComponent>& uicomp){
		bringUIComponentFront(uicomp->getObjectID());
	}
	void TenUI::bringUIComponentFront(unsigned long uicompid){
		vector< sp<DisplayObject> >::iterator it = rootObjs.begin();
		
		vector< sp<DisplayObject> >::iterator rootObjit = rootObjs.end(); 
		while(it != rootObjs.end()){
			if( (*it)->getObjectID() == uicompid ){
				rootObjit = it;
				break;
			}
			++it;
		}
		
		if(it != rootObjs.end()){
			sp<DisplayObject> rootObj = (*rootObjit);
			rootObjs.erase(rootObjit);
			rootObjs.push_back(rootObj);
		}
	}
	
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/		
	void TenUI::draw(){
		vector< sp<DisplayObject> >::iterator it = rootObjs.begin();
		
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
		vector< sp<DisplayObject> >::iterator it = rootObjs.begin();
		while(it != rootObjs.end()){			
			(*it)->update();
			++it;
		}
	}
	
	bool TenUI::isRunning(){
		return running;
	}
		
	void TenUI::addUIComponent(const sp<UIComponent>& uicomp){
		map<unsigned long , sp<UIComponent> >::iterator it = allUIComps.find(uicomp->getObjectID());
		if( it == allUIComps.end() ){
			rootObjs.insert(rootObjs.begin(), uicomp);
			addUIComponent_Recursive(uicomp);	
		}		
	}
	
	void TenUI::addUIComponent_Recursive(const sp<UIComponent>& uicomp){
		cout << "TenUI::addUIComponent_Recursive(): " << uicomp->getObjectID() << endl;
		allUIComps[uicomp->getObjectID()] = uicomp;
		
		vector< sp<DisplayObject> >::const_iterator end = uicomp->getChildren().end();
		vector< sp<DisplayObject> >::const_iterator it = uicomp->getChildren().begin();
		while(it != end){
			sp<UIComponent> child = dynamic_pointer_cast<UIComponent>(*it);
			if(child != NULL){
				addUIComponent_Recursive(child);
			}
			++it;
		}
	}
	
}

