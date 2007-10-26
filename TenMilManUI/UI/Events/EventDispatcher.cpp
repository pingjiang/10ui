#include <iostream>
#include "EventDispatcher.h"

namespace TenUI{

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

bool EventDispatcher::addEvtHandler(std::string evtName, EventHandler* evtHandler)
{
	EventHandler* tmpHandler;
	
	for(std::set<EventHandler*>::iterator iter = registeredEvtHandlers[evtName].begin(); iter != registeredEvtHandlers[evtName].end(); ++iter)
	{
		tmpHandler = *iter;
		
		// objID already exists in registeredEvtHandlers for evtName?
		if(tmpHandler->getEvtHandlerID() == evtHandler->getEvtHandlerID())
		{
			// objID does already exist
			//TODO: throw exception maybe?
			return false;
		}
		
	}

	// objID not found in registeredEvtHandlers for evtName -> add
	registeredEvtHandlers[evtName].insert(evtHandler);	
	return true;
}

void EventDispatcher::displayEvtHandlers()
{
	for(std::map<std::string,std::set<EventHandler*> >::iterator map_iter = registeredEvtHandlers.begin(); map_iter != registeredEvtHandlers.end(); ++map_iter)
	{
		std::cout << map_iter->first << ":\n";
		for(std::set<EventHandler*>::iterator set_iter = (map_iter->second).begin(); set_iter != (map_iter->second).end(); ++set_iter)
			std::cout << *set_iter << "\t" << (*set_iter)->getEvtHandlerID() << "\n";
		std::cout << "\n";
	}
}

}
