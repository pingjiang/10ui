#ifndef UPSTATE_H_
#define UPSTATE_H_

#include <string>
#include <tr1/memory>


#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

using std::string;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
namespace ButtonStates{
	
	class UpState : public UIComponentState, public EventHandler {
	private:
		StateIDType theNextState;

	private:
		int initX;
		int initY;
		
	public:
		static const string STATE_NAME;
		
	public:
		UpState(const shared_ptr<UIComponent>& _uiComp, const string& _stateName = STATE_NAME);
		virtual ~UpState();

		void handleMultiPointEvent(const shared_ptr<Event>& uievent );
		void handlePointIn(const shared_ptr<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
		
		int getInitiatingX();
		int getInitiatingY();
	};
	
}}

#endif /*UPSTATE_H_*/