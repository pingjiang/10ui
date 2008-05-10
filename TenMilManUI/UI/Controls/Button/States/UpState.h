#ifndef UPSTATE_H_
#define UPSTATE_H_

#include <string>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

using std::string;

namespace TenUI{
namespace ButtonStates{
	
	class UpState : public UIComponentState, public EventHandler {
	DECL_STATE(UpState, UIComponentState, Start)
	
	private:
		StateIDType theNextState;

	private:
		int initX;
		int initY;
				
	public:
		virtual ~UpState();

		void handleMultiPointEvent(const sp<Event>& uievent );
		void handlePointIn(const sp<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){}
		
		int getInitiatingX();
		int getInitiatingY();
	};
	
}}

#endif /*UPSTATE_H_*/
