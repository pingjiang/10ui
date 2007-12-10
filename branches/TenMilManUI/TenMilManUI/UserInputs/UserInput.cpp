// user input (mouse or table)

#include "UserInput.h"

namespace TenUI {

	unsigned long UserInput::nextUID = 0;
	unsigned long UserInput::nextUIID = 0;
	unsigned long UserInput::getNextUID()
	{
			return nextUID++;
	}
	
}
