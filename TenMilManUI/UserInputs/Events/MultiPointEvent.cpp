#include "MultiPointEvent.h"

namespace TenUI{

	MultiPointEvent::MultiPointEvent(unsigned long _uid, unsigned long _uiid)
		: UserInputEvent("MultiPointEvent",_uid, _uiid){}
	
	MultiPointEvent::~MultiPointEvent(){}
}
