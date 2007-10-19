// table input

#include "TableInput.h"
#include "InputManager.h"

namespace TenUI {

//bool TableInput::isCreated = false;
//UserInput* TableInput::inst = 0;

UserInput* TableInput::createInstance(){
	TableInput* tbInput = new TableInput;
	InputManager::getInputs()->insert(tbInput);
	return tbInput;
}

UserInput* TableInput::createInstance(long muid){
	//if(!TableInput::isCreated)
	//{
		//TableInput::inst = new TableInput();
		TableInput* tbInput = new TableInput(muid);
		
		//UserInput::inputs.insert(TableInput::inst);
		//InputManager::getInputs()->insert(TableInput::inst);
		InputManager::getInputs()->insert(tbInput);
		//TableInput::isCreated = true;
	//}
	return tbInput;//TableInput::inst;
}

/*UserInput* TableInput::instance(){
	return TableInput::inst;
}*/

}
