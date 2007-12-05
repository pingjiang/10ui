#ifndef USERINPUTEVENT_H_
#define USERINPUTEVENT_H_

#include <TenMilManUI/UI/Events/Event.h>

namespace TenUI {

class UserInputEvent : public Event{
public:
	static const string QUIT_EVENT_TYPE;

private: 
	unsigned long uid;
public:
	UserInputEvent(string _type, unsigned long _uid);
	virtual ~UserInputEvent();
	
	unsigned long getUID(){
		return uid;
	}
};

}
#endif /*USERINPUTEVENT_H_*/
