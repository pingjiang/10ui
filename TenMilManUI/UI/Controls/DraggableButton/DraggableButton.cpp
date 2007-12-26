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
	/*          Construction  		   */
	/***********************************/
	shared_ptr<DraggableButton> DraggableButton::create(){
		shared_ptr<DraggableButton> newButton(new DraggableButton());
		newButton->init();
		return newButton;
	}
	

	/***********************************/
	/*              Event  		       */
	/***********************************/
	void DraggableButton::initEvents(){
		Button::initEvents();
		addEventType(ZoomPointEvent::ZOOM_EVENT_TYPE);
	}
	
	
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	void DraggableButton::initStates(){
		Button::initStates();
		
		// Override ButtonStates::DownState
		stateMachine->registerState(
				shared_ptr<ButtonStates::DragDownState>(
						new ButtonStates::DragDownState(
								dynamic_pointer_cast<UIComponent>(shared_from_this())
						)
				), 
				false);
	}
	
	/***********************************/
	/*              Style              */
	/***********************************/
	void DraggableButton::initStyles(){
		Button::initStyles();
		StyleManager::instance()->registerUIComponent( dynamic_pointer_cast<UIComponent>(shared_from_this()), DraggableButton::getUIComponentName(), Button::getUIComponentName() );
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/


}