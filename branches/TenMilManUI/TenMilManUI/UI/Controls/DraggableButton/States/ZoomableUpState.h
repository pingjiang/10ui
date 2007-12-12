#ifndef ZOOMABLEUPSTATE_H_
#define ZOOMABLEUPSTATE_H_

#include <string>
#include <tr1/memory>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

#include <TenMilManUI/UI/Controls/Button/States/UpState.h>

using std::string;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
namespace ButtonStates{
	
	class ZoomableUpState : public UpState {
	public:
		static const string STATE_NAME;
		
	public:
		ZoomableUpState(const shared_ptr<UIComponent>& _uiComp );
		virtual ~ZoomableUpState();

		void handleMultiPointEvent(const shared_ptr<Event>& uievent );
		void handleZoom(const shared_ptr<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*ZOOMABLEUPSTATE_H_*/
