#include "Button.h"
#include "States/UpState.h"
#include "States/DownState.h"
#include "States/HoverState.h"

#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Style/Styles/ImageStyle.h>
#include <TenMilManUI/UI/Style/Styles/IntStyle.h>
#include <TenMilManUI/UI/Style/Styles/ColorStyle.h>
#include <TenMilManUI/UI/Style/StyleDeclaration.h>


#include <tr1/memory>

using std::tr1::dynamic_pointer_cast;

namespace TenUI{

	IMPL_UICOMP(Button)

	/***********************************/
	/*        	   States              */
	/***********************************/
	BEGIN_IMPL_STATES(Button)
		IMPL_STATE(Button, UpState, ButtonStates::UpState )
		IMPL_STATE(Button, DownState, ButtonStates::DownState )
		IMPL_STATE(Button, HoverState, ButtonStates::HoverState )
	END_IMPL_STATES(Button)
	
	/***********************************/
	/*        	   Styles              */
	/***********************************/
	BEGIN_IMPL_STYLES(Button)
		IMPL_STYLE(Button, bgImage, ImageStyle("") )
		IMPL_STYLE(Button, fillColors, ColorStyle("#800") )
		IMPL_STYLE(Button, borderColors, ColorStyle("#F00") )
		IMPL_STYLE(Button, borderSize, IntStyle(6) )
		IMPL_STYLE(Button, labelColor, ColorStyle("#000") )
		IMPL_STYLE(Button, cornerRadius, IntStyle(5) )
	END_IMPL_STYLES(Button)
	
		

		/** Hover State Styling 
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::HoverState::STATE_NAME,
					StyleDeclaration::create(
							FILL_COLORS_STYLE,
							sp<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,.5)))
					)
			);
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::HoverState::STATE_NAME,
					StyleDeclaration::create(
							BORDER_COLORS_STYLE,
							sp<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,.5)))
					)
			);

		/** Down State Styling 
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::DownState::STATE_NAME,
					StyleDeclaration::create(
							FILL_COLORS_STYLE,
							sp<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,1)))
					)
			);

			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::DownState::STATE_NAME,
					StyleDeclaration::create(
							BORDER_COLORS_STYLE,
							sp<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,1)))
					)
			);*/
	
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void Button::drawSelf(){
		cout << "drawSelf()" << endl;
		
		getTenUIGraphics()->drawRoundedRectangle(	(int)left,(int)bottom, 
													w,h,
													any_cast<int>(curStyleSet->getValue(cornerRadius_style)),
													(any_cast<ColorHex>(curStyleSet->getValue(fillColors_style))).multModifyAlpha(opacity), 
													any_cast<int>(curStyleSet->getValue(borderSize_style)),
													(any_cast<ColorHex>(curStyleSet->getValue(borderColors_style)).multModifyAlpha(opacity)) 
												);
		
		sp<IImage> bgimage = any_cast< sp<IImage> >(curStyleSet->getValue(bgImage_style));
		if(bgimage){
			getTenUIGraphics()->drawImage(bgimage,(int)left+1,(int)bottom+1,.9,w,h);
		}
	}


}
