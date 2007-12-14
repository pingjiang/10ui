#ifndef DRAGDOWNSTATE_H_
#define DRAGDOWNSTATE_H_

#include <string>
#include <tr1/memory>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

#include <TenMilManUI/UI/Controls/Button/States/DownState.h>

#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>

using std::string;
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

namespace TenUI{
namespace ButtonStates{
	
	class DragDownState : public DownState {
	private:
		int offsetX;
		int offsetY;
		
	public:
		static const string STATE_NAME;
		
	public:
		DragDownState(const shared_ptr<UIComponent>& _uiComp );
		virtual ~DragDownState();

		void handleMultiPointEvent(const shared_ptr<Event>& uievent );
		void handlePointMove(const shared_ptr<Event>& uievent );
		void handleZoom(const shared_ptr<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*DRAGDOWNSTATE_H_*/
