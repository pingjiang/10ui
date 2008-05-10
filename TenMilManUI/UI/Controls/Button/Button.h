#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Managers/StyleManager.h>

#include <iostream>

using std::cout;
using std::endl;

namespace TenUI{

	class Button : public UIComponent {
	DECL_UICOMP(Button, UIComponent)

	/***********************************/
	/*        	   States              */
	/***********************************/
	BEGIN_DECLARE_STATES(Button)
		DECLARE_STATE(UpState)
		DECLARE_STATE(DownState)
		DECLARE_STATE(HoverState)
	END_DECLARE_STATES()
	
	/***********************************/
	/*        	   Styles              */
	/***********************************/
	BEGIN_DECLARE_STYLES(Button)
		DECLARE_STYLE(bgImage)
		DECLARE_STYLE(fillColors)
		DECLARE_STYLE(borderColors)
		DECLARE_STYLE(borderSize)
		DECLARE_STYLE(labelColor)
		DECLARE_STYLE(labelAlign)
		DECLARE_STYLE(cornerRadius)
	END_DECLARE_STYLES()
	
	/***********************************/
	/*        	  Properties           */
	/***********************************/
	protected:
		string label;
		const string& 	getLabel(){return label;}
		void 			setLabel(const string& newLabel){label=newLabel;}
		
	
	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
		virtual void drawSelf();
		

	/***********************************/
	/*        	  Destructor           */
	/***********************************/
	public:
		virtual ~Button(){}					
	};

}

#endif /*BUTTON_H_*/
