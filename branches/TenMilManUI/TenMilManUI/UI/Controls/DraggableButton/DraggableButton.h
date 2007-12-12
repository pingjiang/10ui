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
	public:
		DraggableButton(int x, int y, unsigned int w=500, unsigned int h=500):Button(x,y,w,h){}
		virtual ~DraggableButton();
		
		// UIComponent Identification
		virtual string getUIComponentName(){
			return "DraggableButton";
		}

	/***********************************/
	/*        	  Properties           */
	/***********************************/
	protected:
			
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
