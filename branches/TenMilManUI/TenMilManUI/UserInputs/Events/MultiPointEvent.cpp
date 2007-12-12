#include "MultiPointEvent.h"

namespace TenUI{

	const string MultiPointEvent::MULTIPOINT_EVENT_TYPE =		"MultiPointEvent";

	MultiPointEvent::MultiPointEvent(unsigned long _uid, unsigned long _uiid)
		: UserInputEvent(MULTIPOINT_EVENT_TYPE,_uid, _uiid){
		ptEvents = shared_ptr<vector< shared_ptr<PointEvent> > >( new vector< shared_ptr<PointEvent> >() );
	}
	
	MultiPointEvent::~MultiPointEvent(){}
}
