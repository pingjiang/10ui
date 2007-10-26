#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

//#include "Event.h"
#include <iostream>
#include "../../UserInputs/UserInput.h"
#include "Event.h"

namespace TenUI{

class EventHandler
{
private:
	static long nextObjectID;

protected:
	long objid;
	
public:
	EventHandler();
	virtual ~EventHandler();
	
	long getEvtHandlerID(){
		return objid;
	}
	
	virtual bool handleEvent(Event* evt){return false;}
	/*bool process(Event* evt)
	{
		std::cout << "EvtHandler: Handlin'\n";
		return true;
	}*/
	
	// for debugging
	/*void setObjectID(long newid){
		objid = newid;
	}*/
};

}

#endif /*EVENTHANDLER_H_*/
