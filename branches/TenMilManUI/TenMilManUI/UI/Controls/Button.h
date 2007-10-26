#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>

#include <TenMilManUI/UI/Styles/Style.h>
#include <TenMilManUI/UI/Styles/ColorStyle.h>
#include <TenMilManUI/UI/Styles/GradientStyle.h>
#include <TenMilManUI/UI/Styles/HorizontalAlignStyle.h>
#include <TenMilManUI/UI/Styles/IntStyle.h>

#include <iostream>
using namespace std;

namespace TenUI{
	class Button : public UIComponent {
		
	/*##################################/
	/#        	    STATES             #/
	/##################################*/
	protected:
		
	/*##################################/
	/#        	    STYLES             #/
	/##################################*/
	protected:
		GradientStyle* 			fillColors_style;
		GradientStyle* 			borderColors_style;
		
		ColorStyle* 			labelColor_style;
		HorizontalAlignStyle*	labelAlign_style;
		
		IntStyle*				cornerRadius_style;
	
	/*##################################/
	/#        	  ATTRIBUTES           #/
	/##################################*/
	protected:
		string labelText;
		
	public:
		Button(int x, int y, unsigned int w=500, unsigned int h=500):UIComponent(x,y,w,h){}
		virtual ~Button();

		/***********************************/
		/*        Stylable Overrides       */
		/***********************************/
		virtual void initStyles();

		/***********************************/
		/*     DisplayObject Overrides     */
		/***********************************/
			/***********************************/
			/*       Init/Update Methods       */
			/***********************************/
			virtual void update(){}
					
			/***********************************/
			/*           Draw Methods          */
			/***********************************/	
			virtual void draw();
	};
}

#endif /*BUTTON_H_*/
