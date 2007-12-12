#include "DisplayObjectContainer.h"

#include "../../TenUI_Globals.h"

namespace TenUI {	

	DisplayObjectContainer::~DisplayObjectContainer(){
		children.clear();
	}	

	/***********************************/
	/*     Hierarchy Getter/Setters    */
	/***********************************/  
	void DisplayObjectContainer::addChild(shared_ptr<DisplayObject> child){
		child->setParent( shared_from_this() );
		children.push_back(child);
	}	
	void DisplayObjectContainer::removeChild(shared_ptr<DisplayObject> child){
		vector< shared_ptr<DisplayObject> >::iterator it = children.begin();
		unsigned int objid = child->getObjectID();
		while(it != children.end()){
			if((*it)->getObjectID() == objid){
				children.erase(it);
				break;
			}
			++it;
		}
	}
	const vector< shared_ptr<DisplayObject> >& DisplayObjectContainer::getChildren(){
		return children;
	}
	
	/***********************************/
	/*        Init/Update Methods      */
	/***********************************/
	void DisplayObjectContainer::init(){
		// Create the id for the list
		displayListID = glGenLists(1);
		selection_displayListID = glGenLists(1);
		_redraw 	= true;
		_redraw_sel = true;
	}
	void DisplayObjectContainer::update(){
		vector< shared_ptr<DisplayObject> >::iterator it = children.begin();
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
		vector< shared_ptr<DisplayObject> >::iterator it = children.begin();
		while(it != children.end()){
			(*it)->preDraw();
			(*it)->draw();
			(*it)->postDraw();
			++it;
		}
	}
	void DisplayObjectContainer::redraw(){
		_redraw = true;
		_redraw_sel = true;
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void DisplayObjectContainer::draw(){
		if( getTenUIGraphics()->getRenderingMode() == IGraphicsEnums::DISPLAY ){
			if( _redraw ){
				glNewList(displayListID,GL_COMPILE_AND_EXECUTE);
				drawSelf();
				glEndList();
				
				_redraw = false;
			}else{
				glCallList(displayListID);				
			}
		}else{
			if( _redraw_sel ){
				glNewList(selection_displayListID, GL_COMPILE_AND_EXECUTE);
				drawSelf();
				glEndList();
				
				_redraw_sel = false;
			}else{
				glCallList(selection_displayListID);				
			}
		}
		
		getTenUIGraphics()->setClipping(0,0,w,h);
			drawChildren();
		getTenUIGraphics()->resetClipping();
	}
	
	
}
