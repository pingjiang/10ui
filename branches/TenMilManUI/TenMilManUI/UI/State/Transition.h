#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <map>
#include <string>

#include <TenMilManUI/Util/SmartPointer.h>

#include "StateMachineGlobals.h"
#include "StateMachine.h"
#include "State.h"

using std::string;
using std::pair;

namespace TenUI {

	class StateMachine;
	class State;
	
	class Transition {
	public:
		Transition(const StateIDType& _from, const StateIDType& _to);
		virtual ~Transition();
		
		void setStateMachine(const sp<StateMachine>& sm){
			stateMachine = sm;
		}
		
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
