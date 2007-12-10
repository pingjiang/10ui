// header file for mouse input.  you can change between
// mouse input and table input in the main.cpp file by
// commenting out one of the two initialization lines.

#ifndef SDLMOUSEINPUT_H
#define SDLMOUSEINPUT_H

#include <SDL.h>
#include <iostream>

#include "UserInput.h"
#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/UIComponent.h>

namespace TenUI {
	
	class SDLMouseInput : public UserInput {
	protected:	
		SDL_Event event;
		int x,y, dx,dy; // delta x, delta y
		bool pressed, dp; // delta pressed (to see if there's a change)
		
		unsigned long uid;
		
	public:
		SDLMouseInput() : UserInput(),x(-1),y(-1),uid(UserInput::getNextUID()) {
			addEventType(PointEvent::DOWN_EVENT_TYPE);
			addEventType(PointEvent::MOVE_EVENT_TYPE);
			addEventType(PointEvent::UP_EVENT_TYPE);
			pressed = false;
		}
		
		virtual void init() {
			uid = getNextUID();
		}
		
		virtual bool update(){
			string evtType = "";
			dx = 0; dy = 0; dp = false;
			
			SDL_PollEvent( &event );
	
			if( event.type == SDL_ACTIVEEVENT )
			{
				//TODO: Handle entering and exiting windows
				//cout << (event.active.gain == 0 ? "EXITING" : "ENTERING") << " WINDOW\n";
			}
			
			// Handle Mouse
			if( event.type == SDL_MOUSEMOTION )	{
				dx = event.button.x - x;
				x = x + dx;
				
				dy = (getTenUI()->getGraphicsOptions().getHeight() - event.button.y) - y; 
				y = y + dy;
				
				evtType = PointEvent::MOVE_EVENT_TYPE;
			}else if( event.type == SDL_MOUSEBUTTONDOWN && !pressed) {
				dp = true;
				pressed = true;
				evtType = PointEvent::DOWN_EVENT_TYPE;
			}else if( event.type == SDL_MOUSEBUTTONUP && pressed) {
				dp = true;
				pressed = false;
				evtType = PointEvent::UP_EVENT_TYPE;
			
			// Test For Quit
			}else if( event.type == SDL_KEYDOWN ){
				if( event.key.keysym.sym == SDLK_ESCAPE)
	            {
	                quit = true;
				}
			}else if( event.type == SDL_QUIT ) {
		    	quit = true;
		    }  
			
			if( quit ){		
				dispatchEvent(shared_ptr<UserInputEvent>(new UserInputEvent(UserInputEvent::QUIT_EVENT_TYPE, uid, uiid)));
			}else if(evtType != "" && (dx != 0 || dy != 0 || dp)){ 
				dispatchEvent(shared_ptr<PointEvent>(new PointEvent(evtType, uid, uiid,0,x,y,pressed)));
			}	
			
			return true;
		}
		
	};


}

#endif
