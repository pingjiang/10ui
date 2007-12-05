#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"
#include <TenMilManUI/UI/Events/EventHandler.h>
#include <TenMilManUI/UI/Managers/InputManager.h>

using std::string;

namespace TenUI {

	class UIComponent : public DisplayObjectContainer, public EventHandler {
	protected:

	public:
		UIComponent(DisplayObject *p, int x, int y, int w, int h, double rot, double s, double o);
		virtual ~UIComponent();
		
		// SelectManager events
		static string CLICK_EVENT;
		static string PRESS_EVENT;
		static string UNPRESS_EVENT;
		static string HOVER_IN_EVENT;
		static string HOVER_OUT_EVENT;
		static string HOVER_MOVE_EVENT;
		
		// DragManager events
		static string DRAG_ENTER;
		static string DRAG_MOVE;
		static string DRAG_START;
		static string DRAG_EXIT;
		static string DRAG_DROP;
		static string DRAG_COMPLETE;

	};
}

#endif /*UICOMPONENT_H_*/
