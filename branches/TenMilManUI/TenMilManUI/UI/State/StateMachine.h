#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <map>

#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <tr1/memory>

#include <TenMilManUI/UI/Events/EventDispatcher.h>

#include "StateMachineGlobals.h"
#include "State.h"
#include "Transition.h"
#include "Util/hash_pair.h"

using std::pair;
using std::tr1::unordered_map;
using std::tr1::unordered_set;
using std::tr1::shared_ptr;
using std::tr1::enable_shared_from_this;
using std::tr1::hash;

namespace TenUI{
	
	class Transition;
	
	class StateMachine : public EventDispatcher, public enable_shared_from_this<StateMachine> {
	public:
		enum StateMachineException { STATE_ID_DOESNT_EXIST, TRANSITION_DOESNT_EXIST, STATE_ID_REGISTERED_ALREADY, TRANSITION_REGISTER_ALREADY, TRANSITION_ALREADY_SPECIFIED_BY_GENERALIZATION }; 
			
	public:
		StateMachine();
		virtual ~StateMachine();
	
		shared_ptr<State> 		getCurState();
		shared_ptr<Transition> 	getCurTransition();
		
		bool 					registerState(const shared_ptr<State>& newState, bool isStartState=false);
		bool 					registerTransition(const shared_ptr<Transition>& );
	
		shared_ptr<State>		getStartState();
		shared_ptr<State> 		getState(const StateIDType& );
		shared_ptr< unordered_set<StateIDType> > getStateIDs();
		shared_ptr<Transition> 	getTransition(const StateIDType& , const StateIDType& );
		
		bool 					requestStateChange(const StateIDType& nextState);
		
		void 					updateStateMachine();
		
	private: 
		typedef unordered_map< StateIDType, shared_ptr<State>, hash<StateIDType> > StateMapType;
		typedef unordered_map< pair<StateIDType, StateIDType>, shared_ptr<Transition>, hash_pair<StateIDType> > TransitionMapType;
		typedef unordered_map< StateIDType, shared_ptr<Transition>, hash<StateIDType> > AnyStateTransitionMapType;
		
		StateMapType 				states;
	
		// specific transitions
		TransitionMapType 			transitions;
		// generalized transitions (from or to any states)
		AnyStateTransitionMapType 	fromAnyStateStates;
		AnyStateTransitionMapType 	toAnyStateStates;
		// super generalization (from and to anystate);
		shared_ptr<Transition>		anyStateChangeTransition;
		
		shared_ptr<State>			startState;
		shared_ptr<State> 			curState;
		shared_ptr<Transition>		curTransition;
		
	private:
		void changeState(const shared_ptr<State>& newState, const shared_ptr<Transition>& transition);
	};
}

#endif /*STATEMACHINE_H_*/
