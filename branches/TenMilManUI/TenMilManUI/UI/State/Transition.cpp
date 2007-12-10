#include "Transition.h"

#include <iostream>
using std::cout;
using std::endl;

namespace TenUI {
	Transition::Transition(const shared_ptr<StateMachine>& _stateMachine, const StateIDType& _from, const StateIDType& _to){
		stateMachine = _stateMachine;
		fromTo.first = _from;
		fromTo.second = _to;
	}
	Transition::~Transition(){}

	void Transition::init(const StateIDType& _specificFrom, const StateIDType& _specificTo){
		specificFrom = _specificFrom;
		specificTo = _specificTo;
	}
	bool Transition::update(){
		cout << "\t+++ " << fromTo.first << " --> " << fromTo.second << endl;
		return false;
	}
	void Transition::end(){}
	
	const StateIDType& Transition::getFromStateID(){
		return fromTo.first;
	}
	const StateIDType& Transition::getToStateID(){
		return fromTo.second;
	}
	
	const pair<StateIDType, StateIDType>& Transition::getFromToStateIDPair(){
		return fromTo;
	}
}
