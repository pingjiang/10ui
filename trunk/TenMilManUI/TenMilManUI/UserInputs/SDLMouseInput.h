// header file for mouse input.  you can change between
// mouse input and table input in the main.cpp file by
// commenting out one of the two initialization lines.

#ifndef SDLMOUSEINPUT_H
#define SDLMOUSEINPUT_H

#include <SDL.h>
#include <iostream>

#include "UserInput.h"
#include "../TenMilManUI.h"
#include <TenMilManUI/UI/Events/InputEvents/PointEvent.h>


namespace TenUI {

class SDLMouseInput : public UserInput {
protected:
	
	SDL_Event event;
	int x,y;
	bool pressed;
	
	unsigned long uid;
	
public:
	SDLMouseInput() : UserInput(),x(-1),y(-1),uid(UserInput::getNextUID()) {
		/*x = -1;
		y = -1;*/
	}
	
	virtual void init() {}
	virtual bool update(){
		SDL_PollEvent( &event );
		//select = false;
		

		if( event.type == SDL_ACTIVEEVENT )
		{
			//TODO: Handle entering and exiting windows
			//cout << (event.active.gain == 0 ? "EXITING" : "ENTERING") << " WINDOW\n";
		}
		
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
		
		/*if( event.type == SDL_NOEVENT ){
			cout << "SDL NO EVENT" << endl;
		}else{*/
			if( quit ){
				
				cout << "one" << endl;
				//dispatchEvent(shared_ptr<UserInputEvent>(new UserInputEvent(UserInputEvent::QUIT_EVENT_TYPE, uid)));
				//dispatchEvent(shared_ptr<Event>(new Event("sdlfjk")));
			}else{
				cout << "which" << endl;
				//dispatchEvent(shared_ptr<PointEvent>(new PointEvent(PointEvent::MOVE_EVENT_TYPE, uid, x,y,pressed)));
				dispatchEvent(shared_ptr<Event>());
			}
			
		//}

		return true;
	}
	
	/*virtual int getX() { return x; }
	virtual int getY() { return y; }
	virtual bool isPressed() { return pressed; }
	//virtual bool isSelect() { return select; }
	virtual bool isQuit() { return quit; }*/
};


}

#endif
