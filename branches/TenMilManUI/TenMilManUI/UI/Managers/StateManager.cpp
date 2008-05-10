#include "StateManager.h"
#include "UIComponentManager.h"

#include <TenMilManUI/Util/hash_shared_ptr.h>

namespace TenUI{

	sp<StateManager> StateManager::instance(){ 
		static sp<StateManager> myinst(new StateManager());
		return myinst;
	}
	
	StateManager::StateManager(){}
	StateManager::~StateManager(){}
	
	void StateManager::registerUIComponent(const string& uiCompName){
		if( UIComponentManager::instance()->hasRegistered(uiCompName) && !hasRegistered(uiCompName)){
			sp<State_SetType> stateSet( new State_SetType() );
			sp<Transition_SetType> transSet( new Transition_SetType() );
			if(!UIComponentManager::instance()->isRootUIComponent(uiCompName)){
				// Inherit all the states from the super
				const sp<State_SetType>& parentStateSet = getStateSet( UIComponentManager::instance()->getSuperUIComponent(uiCompName) );
				
				if(parentStateSet){
					for( State_SetType::iterator it = parentStateSet->begin();
						 it != parentStateSet->end();
						 ++it){
						stateSet->push_back((*it)->clone());
					}					
				}
				
				const sp<Transition_SetType>& parentTransSet = getTransitionSet( UIComponentManager::instance()->getSuperUIComponent(uiCompName) );

				if(parentTransSet){
					for( Transition_SetType::iterator it = parentTransSet->begin();
						 it != parentTransSet->end();
						 ++it){
						transSet->push_back((*it)->clone());
					}				
				}
							
			}
			
			compStateMap[uiCompName] = stateSet;
			compTransitionMap[uiCompName] = transSet;
			
		}else{
			if( UIComponentManager::instance()->hasRegistered(uiCompName) ) {
				cout << "StateManager::registerUIComponent(): " << uiCompName << " not registered with UIComponentManager." << endl;	
			}else {
				cout << "StateManager::registerUIComponent(): " << uiCompName << " registered with StateManager already." << endl;				
			}
		}
	}
	
	bool StateManager::hasRegistered(const string& uiCompName){
		UIComp_State_MapType::iterator it = compStateMap.find(uiCompName);
		return (it!=compStateMap.end());
	}

	const sp<StateManager::State_SetType>& StateManager::getStateSet(const string& uiCompName){
		if( hasRegistered(uiCompName) ){
			return compStateMap[uiCompName];
		}
		return sp<State_SetType>();
	}
	const sp<StateManager::Transition_SetType>& StateManager::getTransitionSet(const string& uiCompName){
		if( hasRegistered(uiCompName) ){
			return compTransitionMap[uiCompName];
		}
		return sp<Transition_SetType>();
	}
	
	void StateManager::addState(const string& uiCompName, const sp<UIComponentState>& state){
		if( hasRegistered(uiCompName) ){
			cout << "StateManager::addState( " << uiCompName << "," << state->getID() << " )" << endl;
			compStateMap[uiCompName]->push_back(state);
		}
	}
	void StateManager::addTransition(const string& uiCompName, const sp<UIComponentTransition>& trans){
		if( hasRegistered(uiCompName) ){
			compTransitionMap[uiCompName]->push_back(trans);
		}
	}
	sp< StateMachine > StateManager::createStateMachine(const string& uiCompName, const shared_ptr<UIComponent>& uiComp){
		cout << "StateManager::createStateMachine( " << uiCompName << " )" << endl;
		sp< StateMachine > machine;
		if( hasRegistered(uiCompName) ){
			machine = sp<StateMachine>(new StateMachine());
			
			// Add all the states		
			{
				State_SetType::iterator stateit = compStateMap[uiCompName]->begin();
				State_SetType::iterator endit = compStateMap[uiCompName]->end();
				while( stateit != endit ){
					sp<UIComponentState> newState = (*stateit)->clone();
					newState->setUIComponent(uiComp);
					newState->setStateMachine(machine);
					machine->registerState( newState, (((*stateit)->getID()==UIComponent::getStartStateID())?true:false)  );
					++stateit;
				}
			}

			cout << "StateManager::createStateMachine added all states." << endl;
			
			// Add all the transition
			{
				Transition_SetType::iterator transit = compTransitionMap[uiCompName]->begin();
				Transition_SetType::iterator endit = compTransitionMap[uiCompName]->end();
				while( transit != endit ){
					sp<UIComponentTransition> newTrans = (*transit)->clone();
					newTrans->setUIComponent(uiComp);
					newTrans->setStateMachine(machine);
					machine->registerTransition(newTrans);		

					cout << "added a Transition" << endl;
					++transit;
				}
			}
		}else{
			cout << "\t " << uiCompName << " not registered." << endl;
		}
		return machine;
	}
}
