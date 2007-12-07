#include "State.h"

using std::tr1::bind;
using namespace std::tr1::placeholders;

const StateIDType State::ANY_STATE = "*";

State::State(const shared_ptr<StateMachine>& _stateMachine, const string& _id)
			:id(_id) {
	stateMachine = _stateMachine;
}

bool State::exitState(const StateIDType& nextState){
	if(shared_ptr<StateMachine> sm = stateMachine.lock()){
		return sm->requestStateChange(nextState);
	}
	return false;
	//return stateMachine->requestStateChange(nextState);
}
