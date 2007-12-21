#ifndef USERINPUTEVENT_H_
#define USERINPUTEVENT_H_

#include <TenMilManUI/UI/Events/Event.h>
#include "../UserInput_Globals.h"

namespace TenUI {

	class UserInputEvent : public Event {
	friend class InputManager;
		
	public:
		static const string QUIT_EVENT_TYPE;
	
	private:
		UserID_Type 		uid;
		UserInputID_Type 	uiid;
		
	public:
		UserInputEvent(string _type, unsigned long _uid, unsigned long _uiid);
		virtual ~UserInputEvent();
		
		unsigned long getUserID(){
			return uid;
		}

		unsigned long getUserInputID(){
			return uiid;
		}
	};

}
#endif /*USERINPUTEVENT_H_*/
