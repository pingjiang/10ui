#ifndef ZOOMPOINTEVENT_H_
#define ZOOMPOINTEVENT_H_

#include "PointEvent.h"

namespace TenUI {

	class UIComponent;
	
	class ZoomPointEvent : public PointEvent {
	public:
		static const string ZOOM_EVENT_TYPE;
		
	protected:
		int zoomAmount;
		
	public:
		ZoomPointEvent(const string& _type, unsigned long _uid, unsigned long _uiid, unsigned long _pointid, int _zoomAmount, int _x, int _y, const sp<UIComponent>& _target = sp<UIComponent>());
		virtual ~ZoomPointEvent();
		
		int getZoomAmount(){
			return zoomAmount;
		}
	};

}

#endif /*ZOOMPOINTEVENT_H_*/
