// header file for an event
#include <string>

#ifndef EVENT_H
#define EVENT_H

namespace TenUI{

class Event {
	 
public:
	Event(){}
	Event(std::string evt, int mx = -1, int my = -1, bool p = false) : evtName(evt), x(mx), y(my), pressed(p){}
	virtual ~Event(){}

	std::string evtName;
	long id;
	int x, y;
	bool pressed;
	
};

}

#endif
