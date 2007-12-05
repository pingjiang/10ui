#include "InputManager.h"
//#include "../UI/Managers/Manager.h"

namespace TenUI
{

//set<UserInput*> InputManager::inputs;
shared_ptr<InputManager> InputManager::inst;
//InputManager* InputManager::inst;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	inputs.clear();
}

bool InputManager::isQuit(){
	//std::cout << "UserInput::isQuit running...\n";
	if(!inputs.empty())
	{
		//iterates through checking all UserInputs for isQuit()
		for(set<UserInput*>::iterator i = inputs.begin(); i != inputs.end(); ++i)
		{
			//std::cout << (*i) << ": " << (*i)->isQuit() << "\n";
			if((*i)->isQuit())
			{
				cout << "isQuit()\n";
				return true;
			}
		}
		
		return false;
	}
	return true;
}

bool InputManager::update(){
	if(!inputs.empty())
	{
		//iterates through updating all UI
		for(set<UserInput*>::iterator i = inputs.begin(); i != inputs.end(); ++i)
		{
			(*i)->update();			
		}
		return true;
	}
	return false;
}

//TR
shared_ptr<InputManager> InputManager::instance(){
	if(InputManager::inst)
		return InputManager::inst;
	return shared_ptr<InputManager>();
}

/*InputManager* InputManager::instance(){
	if(InputManager::inst)
		return InputManager::inst;
	inst = new InputManager;
	return inst;
}*/

shared_ptr<InputManager> InputManager::createInstance(){
	if(!InputManager::inst){
		InputManager::inst = shared_ptr<InputManager>(new InputManager());
	}
	return InputManager::inst;
}

/*InputManager* InputManager::createInstance() {
	if(!InputManager::inst) {
		InputManager::inst = new InputManager;
	}
	return InputManager::inst;
}*/


set<UserInput*>* InputManager::getInputs() {
	return &inputs;
}

UserInput* InputManager::getInput(unsigned long uiid)
{
	for(set<UserInput*>::iterator i; i != inputs.end(); ++i)
	{
		if((*i)->getUIID() == uiid)
			return *i;
	}
	return NULL;
}

// TR
void InputManager::handleInputEvent(const shared_ptr<Event> &evt){
	/*cout << evt->getType() << '\n';
	shared_ptr<UserInputEvent> inputEvent = dynamic_pointer_cast<UserInputEvent>(evt);*/
	//cout << inputEvent->getUID() << "\n";
}

void InputManager::registerInput(UserInput *ui)
{
	inputs.insert(ui);
	
	ui->registerAllEventsHandler(&InputManager::handleInputEvent,InputManager::inst);
}

}
