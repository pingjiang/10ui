#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <map>
#include <string>
#include <tr1/memory>

#include "StateMachineGlobals.h"
#include "StateMachine.h"
#include "State.h"

using std::string;
using std::pair;
using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
namespace TenUI {

	class StateMachine;
	class State;
	
	class Transition {
	public:
		Transition(const shared_ptr<StateMachine>& _stateMachine, const StateIDType& _from, const StateIDType& _to);
		virtual ~Transition();
		
		virtual void init(const StateIDType& _specificFrom, const StateIDType& _specificTo);
		// Returns	true, 	if transition is not finish
		//			false, 	if transition is finish
		virtual bool update();
		virtual void end();
			
		const StateIDType& getFromStateID();
		const StateIDType& getToStateID();
		
		const pair<StateIDType, StateIDType>& getFromToStateIDPair();
	
	protected:
		StateIDType 	specificFrom;
		StateIDType 	specificTo;
		
	private:
		weak_ptr<StateMachine> 		stateMachine;
		pair<StateIDType, StateIDType> 	fromTo;
		
	};
}

#endif /*TRANSITION_H_*/
