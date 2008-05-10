#ifndef EVENTMACROS_H_
#define EVENTMACROS_H_

#include <TenMilManUI/UI/Core/States/UIComponentState.h>

/** CODE GENERATION BITCHES! **/

#define BEGIN_DECLARE_EVENTS(theClass, theSuperClass) 											\
	private:																					\
		static string theClass##_eventVector_helper(const string& myEventType); 				\
		static vector< string > theClass##EventVector;											\
	protected:																					\
		virtual void initEvents(){																\
			theSuperClass::initEvents();														\
			for(unsigned int i=0; i<theClass##EventVector.size(); ++i){							\
				addEventType(theClass##EventVector.at(i));										\
			}																					\
		}
	
#define DECLARE_EVENT(theClass, theEventName)													\
	private:																					\
		static const string theEventName##_eventVector_helper;									\
	public:																						\
		template<class TC>																		\
		void on##theEventName(void (TC::*f)(EventHandlerArgType), const sp<TC> & inst) {		\
			registerHandler(#theEventName, f, inst);											\
		}
				
#define END_DECLARE_EVENTS(theClass)															\
			

#define BEGIN_IMPL_EVENTS(theClass) 															\
	vector< string > theClass::theClass##EventVector;											\
	string theClass::theClass##_eventVector_helper(const string& myEventType){					\
		theClass##EventVector.push_back(myEventType);											\
		return myEventType;																		\
	}

#define IMPL_EVENT(theClass, theEventName) 														\
	const string theClass::theEventName##_eventVector_helper = theClass::theClass##_eventVector_helper(#theEventName); 

		
#define END_IMPL_EVENTS(theClass) 																\
	

			
#endif /*EVENTMACROS_H_*/
