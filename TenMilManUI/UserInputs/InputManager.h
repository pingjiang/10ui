#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <set>
#include <iostream>
#include "UserInput.h"

namespace TenUI
{

class InputManager
{
	static set<UserInput*> inputs;
	
public:
	InputManager();
	virtual ~InputManager();
	
	static bool isQuit();
	static bool update();	

	static UserInput* instance();
	static set<UserInput*>* getInputs();
	
};

}

#endif /*INPUTMANAGER_H_*/
