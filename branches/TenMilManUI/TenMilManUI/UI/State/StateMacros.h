#ifndef STATEMACROS_H_
#define STATEMACROS_H_

#include <TenMilManUI/UI/Core/States/UIComponentState.h>

/** CODE GENERATION BITCHES! **/

#define BEGIN_DECLARE_STATES(theClass) 															\
	private:																					\
		static bool theClass##_stateInitializer(); 												\
		static const bool theClass##_stateInitializer_helper;									\
	private:																					\
		static StateIDType theClass##_stateVector_helper(const sp<UIComponentState>& newState, const string& myStateName); \
		static const StateIDType theClass##_stateVector_helper_helper;							\
		static vector< sp<UIComponentState> > theClass##StateVector;							\
		static StateIDType theClass##_transVector_helper(const StateIDType& start, const StateIDType& end); \
		static const bool theClass##_transVector_helper_helper;									\
		static vector< sp<UIComponentTransition> > theClass##TransVector;											
	
#define DECLARE_STATE(theStateName)																\
		static const StateIDType theStateName;

#define END_DECLARE_STATES()																	\
			

#define BEGIN_IMPL_STATES(theClass) 															\
	vector< sp<UIComponentState> > theClass::theClass##StateVector;								\
	string theClass::theClass##_stateVector_helper(const sp<UIComponentState>& newState, const string& myStateName){		\
		theClass##StateVector.push_back(newState);												\
		return newState->getID();																\
	}

#define IMPL_STATE(theClass, theStateName, theNewStateClass) 										\
	const StateIDType theClass::theStateName = theClass::theClass##_stateVector_helper(dynamic_pointer_cast<UIComponentState>(sp<theNewStateClass>( new theNewStateClass() )), theNewStateClass::getStateName());

#define IMPL_OVERRIDE_STATE(theClass, theStateName, theNewState) 								\
	StateIDType theClass::theClass##_stateVector_helper_helper = theClass::theClass##_stateVector_helper(theNewState);
		
#define END_IMPL_STATES(theClass) 																\
	bool theClass::theClass##_stateInitializer(){															\
		for(unsigned int i=0; i<theClass##StateVector.size(); ++i){								\
			StateManager::instance()->addState(											\
				theClass::getUICompName(),												\
				theClass##StateVector.at(i)														\
			);																			\
		}																				\
		return false; 																	\
	} 																					\
	const bool theClass::theClass##_stateInitializer_helper = theClass##_stateInitializer();

#endif /*STATEMACROS_H_*/
