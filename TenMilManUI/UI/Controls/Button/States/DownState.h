#ifndef DOWNSTATE_H_
#define DOWNSTATE_H_

#include <string>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

using std::string;

namespace TenUI{
namespace ButtonStates{
	
	class DownState : public UIComponentState, public EventHandler {
	DECL_STATE(DownState, UIComponentState, Down)
		virtual ~DownState();

		void handleMultiPointEvent(const sp<Event>& uievent );
		void handlePointUp(const sp<Event>& uievent );
		void handlePointOut(const sp<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*DOWNSTATE_H_*/
