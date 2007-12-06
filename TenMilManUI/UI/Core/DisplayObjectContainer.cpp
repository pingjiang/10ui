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
	vector<DisplayObject*>* DisplayObjectContainer::getChildren(){
		return &children;
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
	/*      Extended Draw Methods      */
	/***********************************/
	void DisplayObjectContainer::drawChildren(){
		vector<DisplayObject *>::iterator it = children.begin();
		while(it != children.end()){
			(*it)->preDraw();
			(*it)->draw();
			(*it)->postDraw();
			++it;
		}
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void DisplayObjectContainer::draw(){
		drawSelf();
		
		getTenUIGraphics()->setClipping(0,0,w,h);
			drawChildren();
		getTenUIGraphics()->resetClipping();
	}
	
	
}
