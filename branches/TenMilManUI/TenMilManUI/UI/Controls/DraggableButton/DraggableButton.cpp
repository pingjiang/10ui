#include "DraggableButton.h"
#include "States/DragDownState.h"

#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Style/Styles/IntStyle.h>
#include <TenMilManUI/UI/Style/Styles/ColorStyle.h>
#include <TenMilManUI/UI/Style/StyleDeclaration.h>

#include <TenMilManUI/UserInputs/Events/ZoomPointEvent.h>

#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI{

	
	/***********************************/
	/*        	   States              */
	/***********************************/
	BEGIN_IMPL_STATES(DraggableButton)
		IMPL_OVERRIDE_STATE(DraggableButton, DownState, sp<State>(new DragButtonStates::DragDownState()) )
	END_IMPL_STATES(DraggableButton)
	
	/***********************************/
	/*              Event  		       */
	/***********************************/
	void DraggableButton::initEvents(){
		Button::initEvents();
		addEventType(ZoomPointEvent::ZOOM_EVENT_TYPE);
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/


}
