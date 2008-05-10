#ifndef MULTIPOINTEVENT_H_
#define MULTIPOINTEVENT_H_

#include "UserInputEvent.h"
#include "PointEvent.h"

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/Util/SmartPointer.h>

#include <vector>

using std::vector;

namespace TenUI {

	class UIComponent;
		
	class MultiPointEvent : public UserInputEvent {
	public:
		typedef vector< sp<PointEvent> >  PointEventSetType;
		static const string MULTIPOINT_EVENT_TYPE;
		
	protected:		
		sp< vector< sp<PointEvent> > > ptEvents;
		
	public:
		MultiPointEvent(unsigned long _uid, unsigned long _uiid);
		virtual ~MultiPointEvent();

		void addPointEvent(sp<PointEvent> ptEvent){
			ptEvents->push_back(ptEvent);
		}
		const sp< vector<sp<PointEvent> > >& getPointEvents(){
			return ptEvents;
		}
	};

}

#endif /*MULTIPOINTEVENT_H_*/
