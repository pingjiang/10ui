#ifndef STATEMACHINEEVENT_H_
#define STATEMACHINEEVENT_H_

#include <string>

#include "../../FunctorTests/EventPrototype/Event.h"

#include "StateMachineGlobals.h"
#include "State.h"

using std::string;

class StateMachineEvent : public Event {
public: 
	static const string CHANGESTATE_EVENTTYPE;
	
public:
	StateMachineEvent(const StateIDType& _fromid, const StateIDType& _toid, const string& type);
	virtual ~StateMachineEvent();
	
private:
	StateIDType fromid;
	StateIDType toid;
	
};

#endif /*STATEMACHINEEVENT_H_*/
