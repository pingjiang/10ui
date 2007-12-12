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
		visible = true;
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
		unsigned long 	DisplayObject::getObjectID()				{ return objid; }
		shared_ptr<DisplayObject>	DisplayObject::getParent()							{ return this->parent; }
		void 			DisplayObject::setParent(const shared_ptr<DisplayObject>& p)	{ this->parent = p; }
		bool 			DisplayObject::getEnabled()					{ return enabled; }
		void 			DisplayObject::setEnabled(bool e)			{ enabled = e; }
		

	/***********************************/
	/*    Dimensions Getters/Setters   */
	/***********************************/  		
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
		bool   DisplayObject::getVisible()		{ return visible; }
		void   DisplayObject::setVisible(bool e)	{ visible = e; }
		double DisplayObject::getOpacity()		{ return opacity;	}
		void   DisplayObject::setOpacity(float o) { if( o >= 0.0 && o <= 1.0 ){ opacity = o; } }	
	
		
	/***********************************/
	/*  Transformation Getter/Setters  */
	/***********************************/
		
		/*****************/
		/*  Translation  */
		/*****************/
			void 	DisplayObject::setCenterX(int cx){
				x = (2.0*(double)cx)/(scalex*(double)w);
				centerx = cx;
			}
			void 	DisplayObject::setCenterY(int cy){
				y = (2.0*(double)cy)/(scaley*(double)h);
				centery = cy;
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
	

	/*void globalToLocalCoord(int sx, int sy, double *ox, double *oy){
		GLfloat mx = (GLfloat) sx;
		GLfloat my = (GLfloat) sy;
		GLdouble posX, posY, posZ;
		
		//glReadPixels( int(mx), int(my), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mz );
		gluUnProject( mx, my, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

		(*ox) = posX;
		(*oy) = posY;
	}
	
	void localToGlobalCoord(int sx, int sy, int *ox, int *oy){
		GLfloat mx = (GLfloat) sx;
		GLfloat my = (GLfloat) sy;
		GLdouble posX, posY, posZ;
		
		gluProject( mx, my, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

		(*ox) = (int) posX;
		(*oy) = (int) posY;
	}*/

	
}
