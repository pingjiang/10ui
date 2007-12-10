#ifndef POINTEVENT_H_
#define POINTEVENT_H_

#include "UserInputEvent.h"

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <tr1/memory>

using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI {

	class UIComponent;
	
	class PointEvent : public UserInputEvent {
	public:
		static const string IN_EVENT_TYPE;
		static const string OUT_EVENT_TYPE;
		static const string MOVE_EVENT_TYPE;
		static const string UP_EVENT_TYPE;
		static const string DOWN_EVENT_TYPE;
		
	protected:	
		shared_ptr<UIComponent> target;
		unsigned long pointid;
		int x,y;
		bool pressed;
		
	public:
		PointEvent(const string& _type, unsigned long _uid, unsigned long _uiid, unsigned long _pointid, int _x, int _y, bool _pressed);
		virtual ~PointEvent();
	
		int getX(){
			return x;
		}
		int getY(){
			return y;
		}
		bool getPressed(){
			return pressed;
		}

		unsigned long getPointID(){
			return pointid;
		}
		
		const shared_ptr<UIComponent>& getTarget(){
			return target;
		}
	};

}

#endif /*POINTEVENT_H_*/
