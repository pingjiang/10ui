// dynamite comes in small packages.

#include "DisplayObject.h"
#include "../../TenUI_Globals.h"

#include <iostream>
using namespace std;

namespace TenUI {

	/////////////////////////////////////
	//          Private Methods        //
	/////////////////////////////////////
	unsigned long DisplayObject::nextObjectID = 1;
	
	// recalc centerx, centery
	void DisplayObject::calcCenterX() {
		centerx = (int) ((double)x+scalex*(double)w/2.0);
	}
	void DisplayObject::calcCenterY() {
		centery = (int) ((double)y+scaley*(double)h/2.0);
	}
	

	/////////////////////////////////////
	//          Public Methods         //
	/////////////////////////////////////
	DisplayObject::DisplayObject(const shared_ptr<DisplayObject>& p, int x, int y, unsigned int w, unsigned int h, double r, double s, float o){
		objid = ++DisplayObject::nextObjectID;
		
		this->parent = p;
		this->enabled = true;
		
		this->rotation = r;
		this->scalex = s;
		this->scaley = s;
		this->setX(x);
		this->setY(y);

		this->setW(w);
		this->setH(h);		
		
		setOpacity(o);
	}
	

	/***********************************/
	/*           Draw Methods          */
	/***********************************/
		void DisplayObject::preDraw(){
			getTenUIGraphics()->pushViewTransformation(centerx, centery, rotation, scalex, scaley);
		}
	
		void DisplayObject::postDraw(){
			getTenUIGraphics()->popViewTransformation();
		}

	/***********************************/
	/*     Hierarchy Getter/Setters    */
	/***********************************/
		DisplayObjectIDType 		DisplayObject::getObjectID()				{ return objid; }
		shared_ptr<DisplayObject>	DisplayObject::getParent()					{ return this->parent; }
		void 						DisplayObject::setParent(const shared_ptr<DisplayObject>& p)	{ this->parent = p; }
		bool 						DisplayObject::getEnabled()					{ return enabled; }
		void 						DisplayObject::setEnabled(bool e)			{ enabled = e; }
		

	/***********************************/
	/*    Dimensions Getters/Setters   */
	/***********************************/  
		void DisplayObject::setWH(unsigned int nw, unsigned int nh){
			setW(nw);
			setH(nh);
		}
		unsigned int 	DisplayObject::getW(){ return w; }
		void 			DisplayObject::setW(unsigned int nw){
			this->w = nw;
			
			// Recalculate centerx, left
			calcCenterX();
			left = -(double)nw/2.0;
		}

		unsigned int 	DisplayObject::getH(){ return h; }
		void 			DisplayObject::setH(unsigned int nh){
			this->h = nh;
			
			// Recalculate centery, bottom
			calcCenterY();
			bottom = -(double)nh/2.0;
		}
		
		
	/***********************************/
	/*    Visibility Getter/Setters    */
	/***********************************/  
		double DisplayObject::getOpacity()		{ return opacity;	}
		void   DisplayObject::setOpacity(float o) { if( o >= 0.0 && o <= 1.0 ){ opacity = o; } }	
	
		
	/***********************************/
	/*  Transformation Getter/Setters  */
	/***********************************/
		
		/*****************/
		/*  Translation  */
		/*****************/

			void 	DisplayObject::setGlobalCenterXY(int cx, int cy){
				setGlobalCenterX(cx);
				setGlobalCenterY(cy);
			}
			void 	DisplayObject::setGlobalCenterX(int cx){
				setCenterX(cx - ((parent)?parent->getGlobalCenterX():0));
			}
			void 	DisplayObject::setGlobalCenterY(int cy){
				setCenterY(cy - ((parent)?parent->getGlobalCenterY():0));
			}
			int 	DisplayObject::getGlobalCenterX(){
				return ((parent)?parent->getGlobalCenterX():0) + centerx;
			}
			int 	DisplayObject::getGlobalCenterY(){
				return ((parent)?parent->getGlobalCenterY():0)  + centery;
			}

			void 	DisplayObject::setCenterXY(int cx, int cy){
				setCenterX(cx);
				setCenterY(cy);
			}
			void 	DisplayObject::setCenterX(int cx){
				x = (int) ((double)cx - (scalex*(double)w/2.0));
				centerx = cx;
			}
			void 	DisplayObject::setCenterY(int cy){
				y = (int) ((double) cy - (scaley*(double)h/2.0));
				centery = cy;
			}
			int 	DisplayObject::getCenterX(){
				return centerx;
			}
			int 	DisplayObject::getCenterY(){
				return centery;
			}
			

			void 	DisplayObject::setXY(int nx, int ny){
				setX(nx); 
				setY(ny);
			}
			void 	DisplayObject::setX(int nx){
				x = nx;
				calcCenterX();
			}	
			int 	DisplayObject::getX(){ return x; }
			
			void 	DisplayObject::setY(int ny){
				y = ny;
				calcCenterY();				
			}
			int 	DisplayObject::getY(){ return y; }
			
			double 	DisplayObject::getGlobalX(){
				if(parent){
					return parent->getGlobalX() + parent->getScaleX()*x;
				}else{
					return x;
				}
			}			
			double 	DisplayObject::getGlobalY(){
				if(parent){
					return parent->getGlobalY() + parent->getScaleY()*y;
				}else{
					return y;
				}
			}
	
		/*****************/
		/*    Rotation   */
		/*****************/
			double DisplayObject::getRotation(){
				return rotation;
			}
			
			void DisplayObject::setRotation(double r){
				rotation = r;
			}
		
			
			double DisplayObject::getScaleX(){
				return scalex;
			}
			
			void DisplayObject::setScaleX(double s){
				scalex = s;
			}
			
		/*****************/
		/*      Scale    */
		/*****************/		
			double DisplayObject::getScaleY(){
				return scaley;
			}
			
			void DisplayObject::setScaleY(double s){
				scaley = s;
			}
}
