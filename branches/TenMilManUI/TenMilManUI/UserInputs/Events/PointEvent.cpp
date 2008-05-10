#include "PointEvent.h"

namespace TenUI{

	const string PointEvent::IN_EVENT_TYPE =		"PointIn";
	const string PointEvent::OUT_EVENT_TYPE =		"PointOut";
	const string PointEvent::MOVE_EVENT_TYPE =		"PointMove";
	const string PointEvent::UP_EVENT_TYPE =		"PointUp";
	const string PointEvent::DOWN_EVENT_TYPE =		"PointDown";
	
	PointEvent::PointEvent(	const string& _type, 
				unsigned long _uid, 
				unsigned long _uiid, 
				unsigned long _pointid, 
				int _x, 
				int _y, 
				bool _pressed, 
				const sp<UIComponent>& _target)
		: UserInputEvent(_type,_uid, _uiid), pointid(_pointid),x(_x), y(_y), pressed(_pressed), target(_target){}
	
	PointEvent::~PointEvent(){}

}
