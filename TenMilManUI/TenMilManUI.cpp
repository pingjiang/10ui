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
	}	
	TenMilManUI::~TenMilManUI(){
		map<long,DisplayObject*>::iterator it = rootObjs.begin();
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
		cout << "TenMilManUI::run()" << endl;
		
		graphics->init(app->getGraphicsOptions());
		app->init();
		
		cout << "\tapp->init()" << endl;
				
		userInput->update();

		cout << "\tuserInput->update()" << endl;
		while(isRunning() && !userInput->isQuit()){

			cout << "\twhile()" << endl;
			app->update_preframe();
			app->update_frame();
			
			update();

			cout << "\tupdate()" << endl;
			draw();


			cout << "\tdraw()" << endl;
			userInput->update();

			cout << "\tuserInput->update()" << endl;
		}
		
		app->deinit();		
		graphics->deinit();
	}
	
	vector<DisplayObject *> *TenMilManUI::getUIComponentsAt(int x, int y){
		return NULL;
	}
	
	/**********************************
	 * 	 		Private Methods	  	  *	 
	 **********************************/		
	void TenMilManUI::draw(){
		map<long,DisplayObject*>::iterator it = rootObjs.begin();
		
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
	
	void TenMilManUI::addDisplayObject(DisplayObject *obj){
		obj->init();
		
		rootObjs.insert(make_pair(obj->getObjectID(), obj));
	}
				
	
}

