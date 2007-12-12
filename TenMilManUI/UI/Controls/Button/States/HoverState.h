#ifndef HOVERSTATE_H_
#define HOVERSTATE_H_

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
	
	class HoverState : public UIComponentState, public EventHandler {
	public:
		static const string STATE_NAME;
		
	public:
		HoverState(const shared_ptr<UIComponent>& _uiComp );
		virtual ~HoverState();

		void handleMultiPointEvent(const shared_ptr<Event>& uievent );
		void handlePointDown(const shared_ptr<Event>& uievent );
		void handlePointOut(const shared_ptr<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*HOVERSTATE_H_*/
