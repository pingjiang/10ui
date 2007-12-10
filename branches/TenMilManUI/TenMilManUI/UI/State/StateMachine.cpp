#include "StateMachine.h"

#include <iostream>
#include "StateMachineEvent.h"

using std::cout;
using std::endl;
namespace TenUI {
	StateMachine::StateMachine():EventDispatcher(){
		addEventType(StateMachineEvent::CHANGESTATE_EVENTTYPE);
	}
	StateMachine::~StateMachine(){}
	
	bool StateMachine::registerState(const shared_ptr<State>& newState, bool isStartState){
		// Check for duplicate State (by StateID)
		//StateMapType::iterator it = states.find(newState->getID());
		//if( it == states.end() ){
			states[newState->getID()] = newState;
		//	return true;
		//}
		
		if(isStartState){
			curState = newState;
			startState = curState;
			curState->onEnter(State::ANY_STATE);
		}
		
		return false;
	}
	
	bool StateMachine::registerTransition(const shared_ptr<Transition>& newTransition){
		pair<StateIDType, StateIDType> newFromTo = newTransition->getFromToStateIDPair();	
		
		// Check that new transition refers to valid states
		if( (newFromTo.first  == State::ANY_STATE || getState(newFromTo.first)) && 
			(newFromTo.second == State::ANY_STATE || getState(newFromTo.second)) ){
					
			// Setting the super generalization transition
				// [*->*]
				if( newFromTo.first == State::ANY_STATE && newFromTo.second == State::ANY_STATE){
					anyStateChangeTransition = newTransition;
					return true;
					
			// Adding a generalized transition
				// [*->X]
				}else if( newFromTo.first == State::ANY_STATE ){
					fromAnyStateStates[newFromTo.second] = newTransition;
					return true;
											
				// [X->*]
				}else if( newFromTo.second == State::ANY_STATE ){
					toAnyStateStates[newFromTo.first] = newTransition;
					return true;
													
			// Adding a specific transition 
				// [X->Y]
				}else{
					// Check for duplicate transition
					// Check for transition covered by generalized transition 	
					// either [x->*] or [*->x]
					/*if( fromAnyStateStates.find(newFromTo.second) == fromAnyStateStates.end() &&
						toAnyStateStates.find(newFromTo.first) == toAnyStateStates.end() ){*/
						transitions[newFromTo] = newTransition;
						return true;											
					//}
				}
		}
		return false;
	}
	
	shared_ptr<State> 		StateMachine::getCurState(){return curState;}
	shared_ptr<Transition> 	StateMachine::getCurTransition(){return curTransition;}
	shared_ptr<State>		StateMachine::getStartState(){return startState;}
	
	shared_ptr<State> StateMachine::getState(const StateIDType& stateid){
		StateMapType::iterator it = states.find(stateid);
		if( it != states.end() ){
			return it->second;
		}
		return shared_ptr<State>();
	}

	shared_ptr< unordered_set<StateIDType> > StateMachine::getStateIDs(){
		shared_ptr< unordered_set<StateIDType> > idSet( new unordered_set<StateIDType>() );
		for( StateMapType::iterator it = states.begin();
			 it != states.end();
			 ++it){
			idSet->insert(it->first);
		}
		return idSet;
	}
	
	shared_ptr<Transition> StateMachine::getTransition(const StateIDType& from, const StateIDType&  to){
		
		// Check if from and to states exist
		if( (from == State::ANY_STATE 	|| states.find(from) != states.end()) && 
			(to == State::ANY_STATE 	|| states.find(to) != states.end()) 	 ){
			
			AnyStateTransitionMapType::iterator anytransit;
			TransitionMapType::iterator transit; 
			
			// Check if state change request is specified by transition 
			// (in order of precedence)
			
			// 3) Specific
				// [ curState -> nextState ]
				if( (transit = transitions.find(pair<StateIDType, StateIDType>(from, to))) != transitions.end() ){
					return transit->second;
	
			// 2) Generalization
				// [ from -> * ]
				}else if( (anytransit = toAnyStateStates.find(from)) != toAnyStateStates.end() ){
					return anytransit->second;
					
				// [ * -> to ]	
				}else if( (anytransit = fromAnyStateStates.find(to)) != fromAnyStateStates.end() ){
					return anytransit->second;
			
			// 1) Super Generalization 
				// [ * -> * ]	
				}else if( anyStateChangeTransition ){
					return anyStateChangeTransition;
				}
		}
		
		return shared_ptr<Transition>();
	}
	
	
	bool StateMachine::requestStateChange(const StateIDType& nextState){
		if(nextState != State::ANY_STATE){
			shared_ptr<Transition> transition = getTransition(curState->getID(), nextState);
			if( transition ){
				changeState(states[nextState], transition );
				return true;
			}
		}
		return false;
		
		/*StateMapType::iterator stateit = states.find(nextState);
		
		// Check if nextState exists in states
		if( stateit != states.end() ){
			AnyStateTransitionMapType::iterator anytransit;
			TransitionMapType::iterator transit; 
			
			// Check if state change request is specified by transition 
			// (in order of precedence)
			
			// 3) Specific
				// [ curState -> nextState ]
				if( (transit = transitions.find(pair<StateIDType, StateIDType>(curState->getID(), nextState))) != transitions.end() ){
					changeState(stateit->second, transit->second);
					return true;
	
			// 2) Generalization
				// [ curState -> * ]
				}else if( (anytransit = toAnyStateStates.find(curState->getID())) != toAnyStateStates.end() ){
					changeState(stateit->second, anytransit->second);
					return true;
				// [ * -> nextState ]	
				}else if( (anytransit = fromAnyStateStates.find(nextState)) != fromAnyStateStates.end() ){
					changeState(stateit->second, anytransit->second);
					return true;
			
			// 1) Super Generalization 
				// [ * -> * ]	
				}else if( anyStateChangeTransition ){
					changeState(stateit->second, anyStateChangeTransition);
					return true;
				}				
					
		}
		return false;*/
	}
	
	void StateMachine::updateStateMachine(){
		if( curTransition ){
			if( !curTransition->update() ){
				curTransition = shared_ptr<Transition>();
			}
		}else{
			if( curState ){
				curState->update();
			}
		}
	}
	
	void StateMachine::changeState(const shared_ptr<State>& newState, const shared_ptr<Transition>& newTransition){	
		curState->onExit(newState->getID());
		shared_ptr<State> prevState = curState;
		curState = newState;
		curState->onEnter(prevState->getID());
		
		if( curTransition ){
			curTransition->end();
		}
		curTransition = newTransition;
		curTransition->init(prevState->getID(), curState->getID());
		
		dispatchEvent(shared_ptr<StateMachineEvent>(new StateMachineEvent(prevState->getID(), curState->getID(), StateMachineEvent::CHANGESTATE_EVENTTYPE)));	
	}
}