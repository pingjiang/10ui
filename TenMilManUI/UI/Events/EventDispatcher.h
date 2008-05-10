#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

#include <tr1/functional>
#include <tr1/unordered_map>

#include <TenMilManUI/Util/hash_shared_ptr.h>
#include <TenMilManUI/Util/SmartPointer.h>

#include "Event.h"
#include "EventHandler.h"

using std::cout;
using std::endl;

using std::pair;
using std::string;

using std::tr1::bind; 
using std::tr1::function;
using std::tr1::hash;

using std::tr1::unordered_map;

using namespace std::tr1::placeholders;

namespace TenUI {

	class EventDispatcher {
		
	/*******************************
	*			Type Defs 		   *
	********************************/ 
	public:
		typedef const sp<Event>& 											EventHandlerArgType;
		typedef function< void (EventHandlerArgType) >						EventHandlerFuncType;
		
	private:
		typedef pair< sp<EventHandler>, EventHandlerFuncType > 		HandlerPairType;
		typedef unordered_map< 	sp<EventHandler>, 
								EventHandlerFuncType, 
								hash_shared_ptr<EventHandler>
						     > 												HandlerFuncMap;
		typedef unordered_map< string, HandlerFuncMap, hash<string> > 		HandlerMapType;
	
	
	/*******************************
	*		  Member Vars 		   *
	********************************/
	private:
		sp<Event> curEvent;
		function< void (HandlerPairType const &) > dispatchEventFunc;
		HandlerMapType handlers;	
		HandlerFuncMap allEvents_Handlers;
			
	/*******************************
	*		  Helper Funcs 		   *
	********************************/
	private:
		// Used to create dispatchEventFunc
		void _dispatchEvent( HandlerPairType const &handler );
		
	protected:
		void addEventType( const string& );
		void dispatchEvent( sp<Event> const & );	
	
		
	/*******************************
	*		  Public Funcs 		   *
	********************************/
	public:
		EventDispatcher();
		virtual ~EventDispatcher();
		
		template<class TC>
		void registerAllEventsHandler(void (TC::*f)(EventHandlerArgType), const sp<TC> & inst) {
			allEvents_Handlers[inst] = bind(f, inst, _1 );
		}
		
		template<class TC>
		void registerHandler(const string& eventType, void (TC::*f)(EventHandlerArgType), const sp<TC> & inst) {
			HandlerMapType::iterator it = handlers.find(eventType); 
			if( it != handlers.end() ){
				it->second[inst] = bind(f, inst, _1 );
			}
		}
	
		template<class TC>
		void unregisterHandler(const string& eventType, const sp<TC> & inst) {
			HandlerMapType::iterator it = handlers.find(eventType); 
			if( it != handlers.end() ){
				handlers[eventType].erase(inst);
			}
		}
			
	};

}

#endif /*EVENTDISPATCHER_H_*/
