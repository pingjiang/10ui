#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <set>
#include <map>
#include <iostream>
#include <TenMilManUI/UserInputs/UserInput.h>
#include <TenMilManUI/UI/Events/InputEvents/UserInputEvent.h>
#include <TenMilManUI/UI/Events/InputEvents/PointEvent.h>
#include <TenMilManUI/UI/Events/Event.h>


#include <tr1/memory>

using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI {

class InputManager : public EventDispatcher, public EventHandler {
	set<UserInput*> inputs;
	static shared_ptr<InputManager> inst;
	
public:
	InputManager();
	virtual ~InputManager();
	
	bool isQuit();
	bool update();

	static shared_ptr<InputManager> instance();
	static shared_ptr<InputManager> createInstance();
	
	set<UserInput*>* getInputs();
	
	UserInput* getInput(unsigned long uid);
	
	void registerInput(UserInput *ui);
	
	void handleInputEvent(const shared_ptr<Event> &evt);
};

}

#endif /*INPUTMANAGER_H_*/
