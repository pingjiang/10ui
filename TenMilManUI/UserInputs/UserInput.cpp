// user input (mouse or table)

#include "UserInput.h"

namespace TenUI {

char UserInput::MOUSE_INPUT = 'm';
char UserInput::TABLE_INPUT = 't';

char UserInput::REALTIME_DATA = 'r';
char UserInput::GESTURE_DATA = 'g';
char UserInput::BASIC_DATA = 'b';




//set<UserInput*> UserInput::inputs;// = new set<UserInput*>();

/*UserInput* UserInput::instance(){
	if(!UserInput::inputs.empty())
	{
		return *(UserInput::inputs.begin());
	}
	else
		return 0;
}


bool UserInput::isQuit(){
	//std::cout << "UserInput::isQuit running...\n";
	if(!UserInput::inputs.empty())
	{
		//iterates through checking all UserInputs for isQuit()
		for(set<UserInput*>::iterator i = UserInput::inputs.begin(); i != UserInput::inputs.end(); ++i)
		{
			//std::cout << (*i) << ": " << (*i)->isQuit() << "\n";
			if((*i)->getQuit())
				return true;
		}
		
		return false;
	}
	return true;
}

bool UserInput::update(){
	if(!UserInput::inputs.empty())
	{
		//iterates through updating all UI
		for(set<UserInput*>::iterator i = UserInput::inputs.begin(); i != UserInput::inputs.end(); ++i)
		{
			(*i)->run_update();
		}
		return true;
	}
	return false;
}*/

}
