#include "Button.h"
#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

namespace TenUI{

	Button::~Button(){}

	/***********************************/
	/*        Stylable Overrides       */
	/***********************************/
	void Button::initStyles(){
		UIComponent::initStyles();
		
		fillColors_style = new GradientStyle("fillColors",ColorHex("#FFF"));
		addStyle(fillColors_style);
		borderColors_style = new GradientStyle("borderColors",ColorHex("#FFF"));
		addStyle(borderColors_style);
		
		labelColor_style = new ColorStyle("labelColor",ColorHex("#000"));
		addStyle(labelColor_style);				
		labelAlign_style = new HorizontalAlignStyle("labelAlign", HorizontalAlignOptions::CENTER);
		addStyle(labelAlign_style);
		
		cornerRadius_style = new IntStyle("cornerRadius",4);
		addStyle(cornerRadius_style);
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void Button::draw(){
		//getTenUIGraphics()->drawRectangle(0,0,w,h,ColorHex(1,1,1,1),0,ColorHex::NoColor);
		getTenUIGraphics()->drawRoundedRectangle(	0,0, 
													w,h,
													25,
													ColorHex(1,1,1,1), 
													0, ColorHex::NoColor );
		/*getTenUIGraphics()->drawRoundedRectangle(	0,0, 
													w,h,
													cornerRadius_style->getValue(),
													fillColors_style->getValue()[0], 
													0, ColorHex::NoColor );*/
	}

}
