#include "InputManager.h"

namespace TenUI
{

set<UserInput*> InputManager::inputs;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	inputs.clear();
}

bool InputManager::isQuit(){
	//std::cout << "UserInput::isQuit running...\n";
	if(!InputManager::inputs.empty())
	{
		//iterates through checking all UserInputs for isQuit()
		for(set<UserInput*>::iterator i = InputManager::inputs.begin(); i != InputManager::inputs.end(); ++i)
		{
			//std::cout << (*i) << ": " << (*i)->isQuit() << "\n";
			if((*i)->isQuit()) //getQuit()) //TODO: getQuit() -> isQuit()
				return true;
		}
		
		return false;
	}
	return true;
}

bool InputManager::update(){
	if(!InputManager::inputs.empty())
	{
		//iterates through updating all UI
		for(set<UserInput*>::iterator i = InputManager::inputs.begin(); i != InputManager::inputs.end(); ++i)
		{
			(*i)->update(); //run_update(); //TODO: run_update() -> update()
		}
		return true;
	}
	return false;
}

UserInput* InputManager::instance(){
	if(!InputManager::inputs.empty())
	{
		return *(InputManager::inputs.begin());
	}
	else
		return 0;
}


set<UserInput*>* InputManager::getInputs() {
	return &inputs;
}

}
