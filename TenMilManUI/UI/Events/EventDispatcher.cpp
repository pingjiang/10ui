#include "EventDispatcher.h"

#include <iostream>
using std::cout;
using std::endl;

namespace TenUI {

	void EventDispatcher::addEventType( const string& eventType ){
		handlers[eventType] = HandlerFuncMap();
	}
	
	EventDispatcher::EventDispatcher(){
		dispatchEventFunc = bind(&EventDispatcher::_dispatchEvent, this, _1);
	}
	
	EventDispatcher::~EventDispatcher(){}
	
	void EventDispatcher::dispatchEvent(shared_ptr<Event> const & event){
	
		HandlerMapType::iterator it = handlers.find(event->getType()); 
		if( it != handlers.end() ){
			curEvent = event;
	
			HandlerFuncMap::iterator begin = it->second.begin();
			HandlerFuncMap::iterator end = it->second.end();
			
			// Dispatch event to EventHandlers
			for_each(begin, end, dispatchEventFunc);
			
			for_each(allEvents_Handlers.begin(), allEvents_Handlers.end(), dispatchEventFunc);	
		}	
	}
	
	void EventDispatcher::_dispatchEvent( HandlerPairType const &handlerPair ){
		handlerPair.second(curEvent);
	}

}
