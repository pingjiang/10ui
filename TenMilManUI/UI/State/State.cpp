#include "State.h"
#include <iostream>
using std::cout;
using std::endl;
using std::tr1::bind;
using namespace std::tr1::placeholders;

namespace TenUI {
	const StateIDType State::ANY_STATE = "*";
	
	State::State(const string& _id)
				:id(_id) { cout << "\t State()" << id << ";" << endl; }
	
	bool State::exitState(const StateIDType& nextState){
		cout << "\t exitState()" << nextState << ";" << endl;
		if(sp<StateMachine> sm = stateMachine.lock()){
			return sm->requestStateChange(nextState);
		}else{
			cout << "\t !!!couldn't lock" << endl;
		}
		return false;
	}
}
