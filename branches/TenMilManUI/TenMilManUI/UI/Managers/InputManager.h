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

#include <TenMilManUI/Util/SmartPointer.h>

#include <TenMilManUI/UI/Core/UIComponent.h>

#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <vector>

using std::tr1::unordered_map;
using std::tr1::unordered_set;
using std::vector;

namespace TenUI {

class InputManager : public EventDispatcher, public EventHandler {

/***********************************/
/*           Singleton  		   */
/***********************************/
public:
	static sp<InputManager> instance();
private: 
	static sp<InputManager> inst;
	InputManager();

private:
	typedef unordered_map< unsigned long, sp<UserInput> > 							InputMapType;
	typedef unordered_map< unsigned long, unordered_map< unsigned long, unsigned long > > 	UID_PointID_UIComp_MapType;
	typedef unordered_set< unsigned long > UICompIDSet;
	
	InputMapType 				inputs;	
	UID_PointID_UIComp_MapType	UID_PointID_UIComp_Map;	
	
public:
	virtual ~InputManager();
	
	bool isQuit();
	bool update();
	
	sp<UserInput> getInput(unsigned long uid);
	
	void registerInput( const sp<UserInput>& ui);
	

	sp< vector< sp<PointEvent> > > handlePointEvent(const sp<PointEvent> &pointEvent);
	void handleInputEvent(const sp<Event> &evt);
};

}

#endif /*INPUTMANAGER_H_*/
