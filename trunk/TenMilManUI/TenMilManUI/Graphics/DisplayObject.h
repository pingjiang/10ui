// display object is an object to be displayed on the screen.
// it gets extended by other types of display objects such
// as libraryobjects, transformable objects, and selectedobjects.

#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

// includes
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "SDL.h"
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <list>

namespace TenUI {
	
	class DisplayObject {
	public: 
	private:
		static unsigned long nextObjectID;
	
	protected:
		long objid;
	
		// ATTRIBUTES
			// Hierarchy
			DisplayObject *parent;
			
			// Enable/Disable
			bool enabled;
		
			// Positioning
			int x;
			int y;
			
			// Sizing 
			int w;
			int h;
							
			// Scaling
			double scalex;
			double scaley;
	
			// Rotation
			double rotation;
		
			// Visibility
			float opacity;
			bool visible;
				
			
			// OpenGL implementation specifics
			GLint viewport[4];
			GLdouble modelview[16];
			GLdouble projection[16];
			
			double centerx;
			double centery;		
	
			double left;
			double bottom;
		
		// recalc centerx, centery
		virtual void calcCenterX(){
			centerx = (double)x+scalex*(double)w/2.0;
		}
	
		virtual void calcCenterY(){
			centery = (double)y+scaley*(double)h/2.0;
		}
		
		
	public:
		
		// constructor
		DisplayObject(DisplayObject *p, int x, int y, double r=0.0, double s=1.0, float o=1.0){
			objid = DisplayObject::nextObjectID++;
			
			this->parent = p;
			this->enabled = true;
			
			this->rotation = r;
			this->scalex = s;
			this->scaley = s;
			this->setX(x);
			this->setY(y);
			this->parent = 0;
	
			this->setW(10);
			this->setH(10);		
			
			setOpacity(o);
			visible = true;
		}
	
		virtual ~DisplayObject(){}
			
		// Game Loop (and init) function
		virtual void init() = 0;
		virtual void update() = 0;
		
			// Draw Functions
			// Handles setting up the view (translates, scales, rotates)
			// Calls glPushMatrix();
			virtual void preDraw(){
				glPushMatrix();	
				
				// translate, rotate, scale
				glTranslatef((GLdouble)centerx,(GLdouble)centery,0);
				glRotatef((GLfloat)rotation,0,0,1);
				glScalef((GLfloat)this->scalex,(GLfloat)this->scaley,1.0);
				
				// this is for retrieving the mouse coords later
				glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
				glGetDoublev( GL_PROJECTION_MATRIX, projection );
				glGetIntegerv( GL_VIEWPORT, viewport );
			}
			// Draws, most likely to be subclassed
			virtual void draw() = 0;
			// Calls glPopMatrix();
			virtual void postDraw(){
				glPopMatrix();
			}
	
		
		// Getter/Setter Functions
		DisplayObject *getParent(){
			return this->parent;
		}
		
		void setParent(DisplayObject *p){
			this->parent = p;
		}
	
		bool getEnabled(){
			return enabled;
		}
	
		void setEnabled(bool e){
			enabled = e;
		}
		
		bool getVisible(){
			return visible;
		}
	
		void setVisible(bool e){
			visible = e;
		}
		
	
		double getGlobalX(){
			if(parent){
				return parent->getGlobalX() + parent->getScaleX()*x;
			}else{
				return x;
			}
		}
		
		double getGlobalY(){
			if(parent){
				return parent->getGlobalY() + parent->getScaleY()*y;
			}else{
				return y;
			}
		}
		
		virtual void setX(int nx){	
			x = nx;
			
			// Recalculate centerx 
			centerx = (double)x+scalex*(double)w/2.0;
		}	
		virtual int getX(){
			return x;
		}
		
		virtual void setY(int ny){
			y = ny;
			
			// Recalculate centery
			centery = (double)y+scaley*(double)h/2.0;
		}
		virtual int getY(){
			return y;
		}
				
		virtual int getW(){
			return w;
		}
		virtual void setW(int nw){
			this->w = nw;
			
			// Recalculate centerx, left
			calcCenterX();
			left = -(double)nw/2.0;
		}
	
		virtual int getH(){
			return h;
		}
		virtual void setH(int nh){
			this->h = nh;
			
			// Recalculate centery, bottom
			calcCenterY();
			bottom = -(double)nh/2.0;
		}
				
	
		void globalToLocalCoord(int sx, int sy, double *ox, double *oy){
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
			}
		
		// more get, sets
		double getRotation(){
			return rotation;
		}
		
		void setRotation(double r){
			rotation = r;
		}
	
		double getScaleX(){
			return scalex;
		}
		
		void setScaleX(double s){
			scalex = s;
		}
		
		double getScaleY(){
			return scaley;
		}
		
		void setScaleY(double s){
			scaley = s;
		}
		
		double getOpacity(){
			return opacity;
		}
		
		void setOpacity(float o){
			if( o >= 0.0 && o <= 1.0 ){
				opacity = o;
			}
		}	
	
		long getObjectID(){
			return objid;
		}
	};

}

#endif
