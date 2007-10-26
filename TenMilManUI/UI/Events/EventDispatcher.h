#include <map>
#include <set>
#include <string>
#include "EventHandler.h"

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_

namespace TenUI{

class EventDispatcher
{	
public:
	EventDispatcher();
	virtual ~EventDispatcher();
	
	bool addEvtHandler(std::string evtName, EventHandler* evtHandler);
	void displayEvtHandlers();
	
	void dispatchEvent(Event* evt)
	{
		for(std::set<EventHandler*>::iterator i = registeredEvtHandlers[evt->evtName].begin(); i != registeredEvtHandlers[evt->evtName].end(); ++i)
		{
			(*i)->handleEvent(evt);
		}
	}
	
protected:
	std::map<std::string,std::set<EventHandler*> > registeredEvtHandlers;
};

}

#endif /*EVENTDISPATCHER_H_*/
