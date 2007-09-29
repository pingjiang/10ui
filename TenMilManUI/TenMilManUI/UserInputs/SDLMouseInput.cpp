// sdl mouse input

#include "SDLMouseInput.h"

UserInput* SDLMouseInput::createInstance(){
	if(!UserInput::isCreated){
		UserInput::inst = new SDLMouseInput();
	}
	UserInput::isCreated = true;
	return UserInput::inst;
}

UserInput* SDLMouseInput::instance(){
	return UserInput::inst;
}
