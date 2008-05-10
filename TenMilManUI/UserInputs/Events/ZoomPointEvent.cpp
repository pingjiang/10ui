#include "ZoomPointEvent.h"

namespace TenUI{

	const string ZoomPointEvent::ZOOM_EVENT_TYPE = "Zoom";
	
	ZoomPointEvent::ZoomPointEvent(	const string& _type, 
				unsigned long _uid, 
				unsigned long _uiid, 
				unsigned long _pointid,
				int _zoomAmount,
				int _x, 
				int _y, 
				const sp<UIComponent>& _target)
		: PointEvent(_type,_uid, _uiid,_pointid,_x, _y, false, _target), zoomAmount(_zoomAmount){}
	
	ZoomPointEvent::~ZoomPointEvent(){}

}
