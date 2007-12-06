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

		// Fill Colors Style 
		/*{	ArrayStyle* fillColors = new ArrayStyle(ButtonStyles::FILL_COLORS,
													new ColorStyleData(ColorHex("#F00")),
													2);
			fillColor1_style = dynamic_cast<ColorStyleData*>(fillColors->getData(0));
			fillColor2_style = dynamic_cast<ColorStyleData*>(fillColors->getData(1));
			addStyle(fillColors);		}
		
		// Border Styles (colors, sizes)
		{	ArrayStyle* borderColors = new ArrayStyle(	ButtonStyles::BORDER_COLORS,
														new ColorStyleData(ColorHex("#00F")),
														2);
			borderColor1_style = dynamic_cast<ColorStyleData*>(borderColors->getData(0));
			borderColor2_style = dynamic_cast<ColorStyleData*>(borderColors->getData(1));
			addStyle(borderColors);
			borderSize_style = new IntStyleData(5);
			addStyle(new SingleStyle(ButtonStyles::BORDER_SIZE,borderSize_style));		}
		
		// Label Styles		
		labelColor_style = new ColorStyleData(ColorHex("#000")); 
		addStyle(new SingleStyle(ButtonStyles::LABEL_COLOR,labelColor_style));
		
		labelAlign_style = new HorizontalAlignStyleData(); 
		addStyle(new SingleStyle(ButtonStyles::LABEL_ALIGN, labelAlign_style));
		
		// Shape Styles
		cornerRadius_style = new IntStyleData(5);
		addStyle(new SingleStyle(ButtonStyles::CORNER_RADIUS,cornerRadius_style));*/
				
		// Fill Colors Style 
			fillColor1_style = ColorHex("#F00");
			fillColor2_style = ColorHex("#F00");
		
		// Border Style
			borderColor1_style = ColorHex("#0F0");
			borderColor2_style = ColorHex("#0F0");
			borderSize_style = 5;
		
		// Label Styles		
			labelColor_style = ColorHex("#000");
			labelAlign_style = 0; 
		
		// Shape Styles
			cornerRadius_style = 5;		
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void Button::drawSelf(){
		//TODO make left, bottom ints.

		getTenUIGraphics()->drawRectangle(left, bottom, w,h, fillColor1_style, borderSize_style, borderColor1_style);
		/*getTenUIGraphics()->drawRoundedRectangle(	left,bottom, 
													w,h,
													cornerRadius_style,
													fillColor1_style, 
													borderSize_style, borderColor1_style );*/
	}

}
