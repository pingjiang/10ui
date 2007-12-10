#ifndef MULTIPOINTEVENT_H_
#define MULTIPOINTEVENT_H_

#include "UserInputEvent.h"
#include "PointEvent.h"

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <tr1/memory>
#include <vector>

using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;
using std::vector;

namespace TenUI {

	class UIComponent;
		
	class MultiPointEvent : public UserInputEvent {		
	protected:
		shared_ptr< vector< shared_ptr<PointEvent> > > ptEvents;
		
	public:
		MultiPointEvent(unsigned long _uid, unsigned long _uiid);
		virtual ~MultiPointEvent();

		void addPointEvent(shared_ptr<PointEvent> ptEvent){
			ptEvents->push_back(ptEvent);
		}
		const shared_ptr< vector<shared_ptr<PointEvent> > >& getPointEvents(){
			return ptEvents;
		}
	};

}

#endif /*MULTIPOINTEVENT_H_*/
