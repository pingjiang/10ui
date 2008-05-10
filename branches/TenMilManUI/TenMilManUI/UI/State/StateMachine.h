#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <map>

#include <tr1/unordered_map>
#include <tr1/unordered_set>

#include <TenMilManUI/UI/Events/EventDispatcher.h>
#include <TenMilManUI/Util/SmartPointer.h>

#include "StateMachineGlobals.h"
#include "State.h"
#include "Transition.h"
#include "Util/hash_pair.h"

using std::pair;
using std::tr1::unordered_map;
using std::tr1::unordered_set;
using std::tr1::hash;

namespace TenUI{
	
	class Transition;
	
	class StateMachine : public EventDispatcher, public enable_shared_from_this<StateMachine> {
	public:
		enum StateMachineException { STATE_ID_DOESNT_EXIST, TRANSITION_DOESNT_EXIST, STATE_ID_REGISTERED_ALREADY, TRANSITION_REGISTER_ALREADY, TRANSITION_ALREADY_SPECIFIED_BY_GENERALIZATION }; 
			
	public:
		StateMachine();
		virtual ~StateMachine();
	
		sp<State> 		getCurState();
		sp<Transition> 	getCurTransition();
		
		bool 			registerState(const sp<State>& newState, bool isStartState=false);
		bool 			registerTransition(const sp<Transition>& );
	
		sp<State>		getStartState();
		sp<State> 		getState(const StateIDType& );
		sp< unordered_set<StateIDType> > getStateIDs();
		sp<Transition> 	getTransition(const StateIDType& , const StateIDType& );
		
		bool 			requestStateChange(const StateIDType& nextState);
		
		void 			updateStateMachine();
		
	private: 
		typedef unordered_map< StateIDType, sp<State>, hash<StateIDType> > StateMapType;
		typedef unordered_map< pair<StateIDType, StateIDType>, sp<Transition>, hash_pair<StateIDType> > TransitionMapType;
		typedef unordered_map< StateIDType, sp<Transition>, hash<StateIDType> > AnyStateTransitionMapType;
		
		StateMapType 				states;
	
		// specific transitions
		TransitionMapType 			transitions;
		// generalized transitions (from or to any states)
		AnyStateTransitionMapType 	fromAnyStateStates;
		AnyStateTransitionMapType 	toAnyStateStates;
		// super generalization (from and to anystate);
		sp<Transition>		anyStateChangeTransition;
		
		sp<State>			startState;
		sp<State> 			curState;
		sp<Transition>		curTransition;
		
	private:
		void changeState(const sp<State>& newState, const sp<Transition>& transition);
	};
}

#endif /*STATEMACHINE_H_*/
