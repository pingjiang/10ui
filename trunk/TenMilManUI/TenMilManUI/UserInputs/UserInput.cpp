// user input (mouse or table)

#include "UserInput.h"

namespace TenUI {

unsigned long UserInput::nextUID = 0;
unsigned long UserInput::nextUIID = 0;
unsigned long UserInput::getNextUID()
{
		return nextUID++;
}

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
