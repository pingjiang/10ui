#include "Rasterable.h"

namespace TenUI {

	// constructor
	Rasterable::Rasterable(DisplayObject *p, int x, int y, double r, double s, double o)
		:DisplayObject(p,x,y,r,s,o){
	}	
	Rasterable::~Rasterable(){}
		
	// game loop (and init) function
	void Rasterable::init(){}
	void Rasterable::update(){}
	
	void Rasterable::preDraw(){
		DisplayObject::preDraw();
	}
	
	void Rasterable::draw(){		
		if( textureSet ){
			glColor4d(1.0,1.0,1.0,(GLfloat)this->opacity);		
			
			// draw rectangle
			glBegin(GL_QUADS);		                
				glTexCoord2i(0,0); glVertex2d(left,bottom);
				glTexCoord2i(0,1); glVertex2d(left,bottom+texh);
				glTexCoord2i(1,1); glVertex2d(left+texw,bottom+texh);
				glTexCoord2i(1,0); glVertex2d(left+texw,bottom);
			glEnd();
		}
	}
	void Rasterable::postDraw(){
		if(false){ // if( textureSet ){
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}
		DisplayObject::postDraw();
	}
	
	// getter/setter functions				
	// set functions
	void Rasterable::setTextureFromFile(const std::string &fname) throw(int) {
		textureSet = LoadGLTextures(fname.c_str());
		if(!textureSet){
			throw SET_TEXTURE_FAILED;
		}
	}
	
	bool Rasterable::setTexture(GLuint t, int width, int height){
		this->texture = t;
		setW(width);
		setH(height);
		setX(getX());
		setY(getY());
		
		texw = (int) pow(2.0,((int) ceil( log((double)w)/log(2.0) )));
		texh = (int) pow(2.0,((int) ceil( log((double)h)/log(2.0) )));
		
		return (textureSet = true);
	}
	
	// get functions
	GLuint Rasterable::getTexture(){
		return texture;	
	}

}
