#include "StateMachineEvent.h"
namespace TenUI {
	const string StateMachineEvent::CHANGESTATE_EVENTTYPE("CHANGESTATE");
	StateMachineEvent::StateMachineEvent(const StateIDType& _fromid, const StateIDType& _toid, const string& type)
		:Event(type),
		 fromid(_fromid),
		 toid(_toid){}
	
	StateMachineEvent::~StateMachineEvent(){}
}
