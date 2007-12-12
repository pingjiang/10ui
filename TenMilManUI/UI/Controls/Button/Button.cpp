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

	Button::~Button(){}
	
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	void Button::initStates(){
		UIComponent::initStates();
		
		stateMachine->registerState(
				shared_ptr<ButtonStates::UpState>(
						new ButtonStates::UpState(
								dynamic_pointer_cast<UIComponent>(shared_from_this())
						)
				), 
				true);
		
		stateMachine->registerState(
				shared_ptr<ButtonStates::HoverState>(
						new ButtonStates::HoverState(
								dynamic_pointer_cast<UIComponent>(shared_from_this())
						)
				), 
				false);
		
		stateMachine->registerState(
				shared_ptr<ButtonStates::DownState>(
						new ButtonStates::DownState(
								dynamic_pointer_cast<UIComponent>(shared_from_this())
						)
				), 
				false);
	}
	
	/***********************************/
	/*              Style              */
	/***********************************/
	const string Button::BACKGROUND_IMAGE("bgImage");
	const string Button::FILL_COLORS_STYLE("fillColors");
	const string Button::BORDER_COLORS_STYLE("borderColors");
	const string Button::BORDER_SIZE_STYLE("borderSize");
	const string Button::LABEL_COLOR_STYLE("labelColor");
	const string Button::LABEL_ALIGN_STYLE("labelAlign");
	const string Button::CORNER_RADIUS_STYLE("cornerRadius");
		
	void Button::initStyles(){
		UIComponent::initStyles();
		StyleManager::instance()->registerUIComponent( dynamic_pointer_cast<UIComponent>(shared_from_this()), Button::getUIComponentName(), UIComponent::getUIComponentName() );

		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						CORNER_RADIUS_STYLE,
						shared_ptr<IntStyle>(new IntStyle(5))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
						Button::getUIComponentName(), 
						StyleDeclaration::create(
								BACKGROUND_IMAGE,
								shared_ptr<ImageStyle>(new ImageStyle(""))
						)
		);

		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						FILL_COLORS_STYLE,
						shared_ptr<ColorStyle>(new ColorStyle("#800"))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						BORDER_COLORS_STYLE,
						shared_ptr<ColorStyle>(new ColorStyle(ColorHex(1.0,0.0,0.0,0.0)))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						BORDER_SIZE_STYLE,
						shared_ptr<IntStyle>(new IntStyle(6))
				)
		);
		
		StyleManager::instance()->addStyleDeclaration(
				Button::getUIComponentName(), 
				StyleDeclaration::create(
						LABEL_COLOR_STYLE,
						shared_ptr<ColorStyle>(new ColorStyle("#000"))
				)
		);
			
		

		/** Hover State Styling **/
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::HoverState::STATE_NAME,
					StyleDeclaration::create(
							FILL_COLORS_STYLE,
							shared_ptr<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,.5)))
					)
			);
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::HoverState::STATE_NAME,
					StyleDeclaration::create(
							BORDER_COLORS_STYLE,
							shared_ptr<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,.5)))
					)
			);

		/** Down State Styling **/
			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::DownState::STATE_NAME,
					StyleDeclaration::create(
							FILL_COLORS_STYLE,
							shared_ptr<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,1)))
					)
			);

			StyleManager::instance()->setStateStyleDeclaration(
					Button::getUIComponentName(),
					ButtonStates::DownState::STATE_NAME,
					StyleDeclaration::create(
							BORDER_COLORS_STYLE,
							shared_ptr<ColorStyle>(new ColorStyle(ColorHex(1.0,0,0,1)))
					)
			);

	}
	
	/***********************************/
	/*           Draw Methods          */
	/***********************************/
	void Button::drawSelf(){
		int strokeSize = any_cast<int>(curStyleSet->getValue(BORDER_SIZE_STYLE));
		getTenUIGraphics()->drawRoundedRectangle(	left,bottom, 
													w,h,
													any_cast<int>(curStyleSet->getValue(CORNER_RADIUS_STYLE)),
													(any_cast<ColorHex>(curStyleSet->getValue(FILL_COLORS_STYLE))).multModifyAlpha(opacity), 
													strokeSize,
													(any_cast<ColorHex>(curStyleSet->getValue(BORDER_COLORS_STYLE)).multModifyAlpha(opacity)) 
												);
		
		IImage* bgimage = any_cast<IImage*>(curStyleSet->getValue(BACKGROUND_IMAGE));
		if(bgimage != 0){
			getTenUIGraphics()->drawImage(bgimage,left+1,bottom+1,.9,w,h);
		}
	}


}
