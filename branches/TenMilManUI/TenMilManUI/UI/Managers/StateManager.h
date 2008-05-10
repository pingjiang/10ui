#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>
#include <TenMilManUI/UI/Core/Transitions/UIComponentTransition.h>

#include <TenMilManUI/UI/State/StateMachine.h>

#include <TenMilManUI/Util/SmartPointer.h>

#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

using std::string;
using std::vector;
using std::tr1::unordered_map;
using std::tr1::unordered_set;

namespace TenUI{

	class UIComponent;
	class UIComponentState;
	class UIComponentTransition;
			
	class StateManager {
		/**
		 * Private Typedefs
		 */
	private:
		typedef vector< sp<UIComponentTransition> > 			Transition_SetType;
		typedef vector< sp<UIComponentState> > 					State_SetType; 
		typedef unordered_map< string, sp<State_SetType> > 		UIComp_State_MapType;
		typedef unordered_map< string, sp<Transition_SetType> > UIComp_Transition_MapType;
	
		/**
		 * Singleton
		 */
	public:
		static sp<StateManager> instance();
	private:
		StateManager();

	private:
		UIComp_State_MapType 		compStateMap;
		UIComp_Transition_MapType 	compTransitionMap;
		
	public:
		virtual ~StateManager();
		
		void registerUIComponent(const string& uiCompName);	
		bool hasRegistered(const string& uiCompName);

		const sp<State_SetType>& getStateSet(const string& uiCompName);
		const sp<Transition_SetType>& getTransitionSet(const string& uiCompName);
		
		void addState(const string& uiCompName, const sp<UIComponentState>& state);	
		void addTransition(const string& uiCompName, const sp<UIComponentTransition>& state);
		sp< StateMachine > createStateMachine(const string& uiCompName, const shared_ptr<UIComponent>& uiComp);
		
	};
	
}
#endif /*STATEMANAGER_H_*/
