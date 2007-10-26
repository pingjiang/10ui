// sdl mouse input

#include "SDLMouseInput.h"
#include "InputManager.h"
#include <iostream>

namespace TenUI {

bool SDLMouseInput::isCreated = false;
UserInput* SDLMouseInput::inst = 0;

UserInput* SDLMouseInput::createInstance(){
	if(!SDLMouseInput::isCreated)
	{
		SDLMouseInput::inst = new SDLMouseInput();
		//UserInput::inputs.insert(SDLMouseInput::inst);
		InputManager::getInputs()->insert(SDLMouseInput::inst);
		SDLMouseInput::isCreated = true;
	}
	return SDLMouseInput::inst;
}

UserInput* SDLMouseInput::instance(){
	return SDLMouseInput::inst;
}

}
