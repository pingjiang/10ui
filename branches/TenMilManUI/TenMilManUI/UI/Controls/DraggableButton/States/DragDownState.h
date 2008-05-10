#ifndef DRAGDOWNSTATE_H_
#define DRAGDOWNSTATE_H_

#include <string>

#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UserInputs/Events/UserInputEvent.h>
#include <TenMilManUI/UserInputs/Events/PointEvent.h>
#include <TenMilManUI/UI/Core/States/UIComponentState.h>

#include <TenMilManUI/UI/Controls/Button/States/DownState.h>

#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>

using std::string;

namespace TenUI{
namespace ButtonStates{
	
	class DragDownState : public DownState {
	DECL_STATE(DragDownState, DownState, Down)
		
	private:
		int offsetX;
		int offsetY;
		
	public:
		virtual ~DragDownState();

		void handleMultiPointEvent(const sp<Event>& uievent );
		void handlePointMove(const sp<Event>& uievent );
		void handleZoom(const sp<Event>& uievent );
		
		virtual void onEnter(const StateIDType& prevState);
		virtual void onExit(const StateIDType& nextState);
		
		virtual void update(){};
	};
	
}}

#endif /*DRAGDOWNSTATE_H_*/
