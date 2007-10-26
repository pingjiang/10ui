#include "DisplayObjectContainer.h"

namespace TenUI {	

	DisplayObjectContainer::~DisplayObjectContainer(){
		children.clear();
	}
	

	void DisplayObjectContainer::update(){
		vector<DisplayObject *>::iterator it = children.begin();
		while(it != children.end()){
			(*it)->update();
		}
	}
	
	void DisplayObjectContainer::preDraw(){
		//InteractiveObject::preDraw();
		
		glEnable(GL_SCISSOR_TEST);
		glScissor(0,0, w, h);
	}
	void DisplayObjectContainer::draw(){
			vector<DisplayObject *>::iterator it = children.begin();
			while(it != children.end()){
				(*it)->preDraw();
				(*it)->draw();
				(*it)->postDraw();
			}
	}
	void DisplayObjectContainer::postDraw(){
		glDisable(GL_SCISSOR_TEST);

		//InteractiveObject::postDraw();
	}
	
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
	
}
