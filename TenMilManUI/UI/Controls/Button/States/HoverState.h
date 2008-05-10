#ifndef HOVERSTATE_H_
#define HOVERSTATE_H_

#include <string>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

using std::string;

namespace TenUI{
namespace ButtonStates{
	
	class HoverState : public UIComponentState, public EventHandler {
	DECL_STATE(HoverState, UIComponentState, Hover)
	
	private:
		int initX;
		int initY;
			
	public:
		virtual ~HoverState();

		void handleMultiPointEvent(const sp<Event>& uievent );
		void handlePointDown(const sp<Event>& uievent );
		void handlePointOut(const sp<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);

		int getInitiatingX();
		int getInitiatingY();
		
		virtual void update(){};
	};
	
}}

#endif /*HOVERSTATE_H_*/
