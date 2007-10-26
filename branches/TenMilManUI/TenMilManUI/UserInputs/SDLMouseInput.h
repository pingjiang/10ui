// header file for mouse input.  you can change between
// mouse input and table input in the main.cpp file by
// commenting out one of the two initialization lines.

#ifndef SDLMOUSEINPUT_H
#define SDLMOUSEINPUT_H

#include <SDL.h>

//#include "UserInput.h"
#include "BasicInput.h"
#include "../TenMilManUI.h"

namespace TenUI {

//class SDLMouseInput : UserInput {
class SDLMouseInput : public BasicInput {
protected:
	static bool isCreated;
	static UserInput* inst;
	
	SDL_Event event;
	long fid, uid; // "finger" id, user id (table side)
	int x,y;
	bool pressed;//, select;
	bool quit;
	
public:
	//SDLMouseInput() : UserInput() {
	SDLMouseInput() : BasicInput() {
		UI_type = UserInput::MOUSE_INPUT;
		x = -1;
		y = -1;
		fid = 0;
		uid = 0;
		quit = false;
	}
	
	static UserInput* createInstance();
	static UserInput* instance();
	
	virtual void init() {}
	virtual bool update(){
		SDL_PollEvent( &event );
		
		//select = false;

		if( event.type == SDL_MOUSEMOTION )
		{
			x = event.button.x;
			y = getTenUI()->getScreenHeight() - event.button.y;
		}

		if( event.type == SDL_MOUSEBUTTONDOWN && !pressed)
		{
			pressed = true;
		}

		if( event.type == SDL_MOUSEBUTTONUP )
		{
			pressed = false;
			//select = true;
		}

		if( event.type == SDL_KEYDOWN )
        {
			if( event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
			}
		}
	    else if( event.type == SDL_QUIT )
	    {
	    	quit = true;
	    }  

		return true;
	}
	
	virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual bool isPressed() { return pressed; }
	//virtual bool isSelect() { return select; }
	virtual bool isQuit() { return quit; }
};


}

#endif
