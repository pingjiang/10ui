#include "DisplayObjectContainer.h"

#include "../../TenUI_Globals.h"

namespace TenUI {	

	DisplayObjectContainer::~DisplayObjectContainer(){
		children.clear();
	}	

	/***********************************/
	/*     Hierarchy Getter/Setters    */
	/***********************************/  
	void DisplayObjectContainer::addChild(DisplayObject* child){
		child->setParent(this);
		children.push_back(child);
	}	
	void DisplayObjectContainer::removeChild(DisplayObject* child){
		vector<DisplayObject *>::iterator it = children.begin();
		int objid = child->getObjectID();
		while(it != children.end()){
			if((*it)->getObjectID() == objid){
				children.erase(it);
				break;
			}
			++it;
		}
	}
	
	/***********************************/
	/*        Init/Update Methods      */
	/***********************************/
	void DisplayObjectContainer::init(){}
	void DisplayObjectContainer::update(){
		vector<DisplayObject *>::iterator it = children.begin();
		while(it != children.end()){
			(*it)->update();
			++it;
		}
	}
	void DisplayObjectContainer::deinit(){}	
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void DisplayObjectContainer::preDraw(){
		DisplayObject::preDraw();
				
		getTenUIGraphics()->setClipping(0,0,w,h);
	}
	void DisplayObjectContainer::draw(){
		vector<DisplayObject *>::iterator it = children.begin();
		while(it != children.end()){
			(*it)->preDraw();
			(*it)->draw();
			(*it)->postDraw();
			++it;
		}
	}
	void DisplayObjectContainer::postDraw(){
		getTenUIGraphics()->resetClipping();
		
		DisplayObject::postDraw();
	}
	
	
}
