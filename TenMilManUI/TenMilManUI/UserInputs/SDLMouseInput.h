// header file for mouse input.  you can change between
// mouse input and table input in the main.cpp file by
// commenting out one of the two initialization lines.

#ifndef SDLMOUSEINPUT_H
#define SDLMOUSEINPUT_H

#include <SDL.h>
#include "UserInput.h"
#include "../Globals.h"

class SDLMouseInput : UserInput {
protected:
	SDL_Event event;	

	SDLMouseInput():UserInput(){}
	virtual ~SDLMouseInput(){}

public:
	static UserInput* createInstance();
	static UserInput* instance();

	virtual bool update(){
		SDL_PollEvent( &event );
		indata.select = false;

		if( event.type == SDL_MOUSEMOTION )
		{
			indata.x = event.button.x;
			indata.y = SCREEN_HEIGHT - event.button.y;
		}
		if( event.type == SDL_MOUSEBUTTONDOWN && !indata.pressed)
		{
			indata.pressed = true;
		}
		if( event.type == SDL_MOUSEBUTTONUP )
		{
			indata.pressed = false;
			indata.select = true;
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
	

};

#endif
