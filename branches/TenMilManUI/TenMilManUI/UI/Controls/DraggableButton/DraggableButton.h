#ifndef DRAGGABLEBUTTON_H_
#define DRAGGABLEBUTTON_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Managers/StyleManager.h>
#include <TenMilManUI/UI/Controls/Button/Button.h>

#include <iostream>

using std::cout;
using std::endl;

namespace TenUI{

	class DraggableButton : public Button {
	DECL_UICOMP(DraggableButton, Button)
	
	/***********************************/
	/*        	   States              */
	/***********************************/
	BEGIN_DECLARE_STATES(DraggableButton)
		DECLARE_STATE(DownState)
	END_DECLARE_STATES()
	
	/***********************************/
	/*        	   Styles              */
	/***********************************/
	BEGIN_DECLARE_STYLES(Button)
		DECLARE_STYLE(bgImage)
		
		
	/***********************************/
	/*              Event  		       */
	/***********************************/
	protected:
		virtual void initEvents();
				
	public:
		virtual ~DraggableButton(){}			
	};
}

#endif /*DRAGGABLEBUTTON_H_*/
