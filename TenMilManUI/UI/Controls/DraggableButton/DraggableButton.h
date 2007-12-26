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
		

	/** @name Construction 
	 */
	//@{
	public:
		/**
		 * Creates a new Button.
		 */
		static shared_ptr<DraggableButton> create();
	//@}
				
	public:
		virtual ~DraggableButton(){}
		
		// UIComponent Identification
		virtual string getUIComponentName(){
			return "DraggableButton";
		}

	/***********************************/
	/*        	  Properties           */
	/***********************************/
	protected:
			
	/***********************************/
	/*              Event  		       */
	/***********************************/
	protected:
		virtual void initEvents();
		
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	protected:
		virtual void initStates();
		
	/***********************************/
	/*        	    Style  			   */
	/***********************************/
	protected:
		virtual void initStyles();

	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
					
	};
}

#endif /*DRAGGABLEBUTTON_H_*/
