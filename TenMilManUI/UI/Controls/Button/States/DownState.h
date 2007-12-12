#ifndef DOWNSTATE_H_
#define DOWNSTATE_H_

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
	
	class DownState : public UIComponentState, public EventHandler {
	public:
		static const string STATE_NAME;
		
	public:
		DownState(const shared_ptr<UIComponent>& _uiComp);
		virtual ~DownState();

		void handleMultiPointEvent(const shared_ptr<Event>& uievent );
		void handlePointUp(const shared_ptr<Event>& uievent );
		void handlePointOut(const shared_ptr<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*DOWNSTATE_H_*/
