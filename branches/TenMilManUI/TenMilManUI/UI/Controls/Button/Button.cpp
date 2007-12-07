#include "Button.h"
#include <TenMilManUI/TenUI_Globals.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Style/Styles/IntStyle.h>
#include <TenMilManUI/UI/Style/Styles/ColorStyle.h>
#include <TenMilManUI/UI/Style/StyleDeclaration.h>

namespace TenUI{

	Button::~Button(){}
	
	/***********************************/
	/*        Stylable Overrides       */
	/***********************************/
	void Button::initStyles(){
		UIComponent::initStyles();
		StyleManager::instance()->registerUIComponent( dynamic_pointer_cast<UIComponent>(shared_from_this()), Button::getUIComponentName(), UIComponent::getUIComponentName() );

		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						ButtonStyles::CORNER_RADIUS,
						shared_ptr<IntStyle>(new IntStyle(20))
				)
		);

		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						ButtonStyles::FILL_COLORS,
						shared_ptr<ColorStyle>(new ColorStyle("#F00"))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						ButtonStyles::BORDER_COLORS,
						shared_ptr<ColorStyle>(new ColorStyle("#00F"))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						ButtonStyles::BORDER_SIZE,
						shared_ptr<IntStyle>(new IntStyle(5))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						ButtonStyles::LABEL_COLOR,
						shared_ptr<ColorStyle>(new ColorStyle("#000"))
				)
		);
			
	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void Button::drawSelf(){
		getTenUIGraphics()->drawRoundedRectangle(	left,bottom, 
													w,h,
													any_cast<int>(curStyleSet->getValue(ButtonStyles::CORNER_RADIUS)),
													any_cast<ColorHex>(curStyleSet->getValue(ButtonStyles::FILL_COLORS)), 
													any_cast<int>(curStyleSet->getValue(ButtonStyles::BORDER_SIZE)),
													any_cast<ColorHex>(curStyleSet->getValue(ButtonStyles::BORDER_COLORS)) 
												);
		
	}


}
