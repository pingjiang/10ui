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
	//#include <GL/glaux.h>
#endif

#include "SDL.h"
#include <SDL_image.h>
#include <math.h>
#include <string>
#include <list>


class DisplayObject {
public: 
private:
	static long nextObjectID;

protected:
	long objid;

	// ATTRIBUTES
		// Hierarchy
		DisplayObject *parent;
		
		// Enable/Disable
		bool isEnable;
	
		// Positioning
		int x;
		int y;
				
		// Scaling
		double scalex;
		double scaley;

		// Rotation
		double rotation;
	
		// Visibility
		float opacity;
	
	// OpenGL implementation specifics
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	
public:
	
	// constructor
	DisplayObject(DisplayObject *p, int x, int y, double r=0.0, double s=1.0, float o=1.0){
		objid = DisplayObject::nextObjectID++;
		
		this->parent = p;
		this->isEnable = true;
		
		this->rotation = r;
		this->scalex = s;
		this->scaley = s;
		this->setX(x);
		this->setY(y);
		this->parent = 0;
		
		setOpacity(o);
	}

	virtual ~DisplayObject(){}
		
	// game loop (and init) function
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	
	// Getter/Setter Functions
	DisplayObject *getParent(){
		return this->parent;
	}
	
	void setParent(DisplayObject *p){
		this->parent = p;
	}

	bool isEnabled(){
		return isEnable;
	}

	void setEnabled(bool e){
		isEnable = e;
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
	
	int getX(){
		return x;
	}
	
	int getY(){
		return y;
	}
	
	virtual void setX(int nx){
		x = nx;
	}
	
	virtual void setY(int ny){
		y = ny;
	}

	void globalToLocalCoord(int sx, int sy, double *ox, double *oy){
		GLfloat mx = (GLfloat) sx;
		GLfloat my = (GLfloat) sy;
		GLfloat mz;
		GLdouble posX, posY, posZ;
		
		glReadPixels( int(mx), int(my), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mz );

		gluUnProject( mx, my, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);

		(*ox) = posX;
		(*oy) = posY;
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

#endif
