#ifndef POINTEVENT_H_
#define POINTEVENT_H_

#include "UserInputEvent.h"

namespace TenUI {

class PointEvent : public UserInputEvent
{
public:
	static const string MOVE_EVENT_TYPE;
	static const string UP_EVENT_TYPE;
	static const string DOWN_EVENT_TYPE;
	
protected:
	int x,y;
	bool pressed;
	
public:
	PointEvent(string _type, unsigned long _uid, int _x, int _y, bool _pressed);
	virtual ~PointEvent();
};

}

#endif /*POINTEVENT_H_*/
