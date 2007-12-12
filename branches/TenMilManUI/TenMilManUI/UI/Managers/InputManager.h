#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <set>
#include <map>
#include <iostream>

#include <TenMilManUI/UserInputs/UserInput.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/MultiPointEvent.h>
#include <TenMilManUI/UI/Events/Event.h>

#include <TenMilManUI/UI/Core/UIComponent.h>

#include <tr1/memory>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <vector>

using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;
using std::tr1::unordered_map;
using std::tr1::unordered_set;
using std::vector;

namespace TenUI {

class InputManager : public EventDispatcher, public EventHandler {

/***********************************/
/*           Singleton  		   */
/***********************************/
public:
	static shared_ptr<InputManager> instance();
private: 
	static shared_ptr<InputManager> inst;
	InputManager();

private:
	typedef unordered_map< unsigned long, shared_ptr<UserInput> > 							InputMapType;
	typedef unordered_map< unsigned long, unordered_map< unsigned long, unsigned long > > 	UID_PointID_UIComp_MapType;
	typedef unordered_set< unsigned long > UICompIDSet;
	
	InputMapType 				inputs;	
	UID_PointID_UIComp_MapType	UID_PointID_UIComp_Map;	
	
public:
	virtual ~InputManager();
	
	bool isQuit();
	bool update();
	
	shared_ptr<UserInput> getInput(unsigned long uid);
	
	void registerInput( const shared_ptr<UserInput>& ui);
	

	shared_ptr< vector< shared_ptr<PointEvent> > > handlePointEvent(const shared_ptr<PointEvent> &pointEvent);
	void handleInputEvent(const shared_ptr<Event> &evt);
};

}

#endif /*INPUTMANAGER_H_*/
