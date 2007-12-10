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
	public:
		Button(int x, int y, unsigned int w=500, unsigned int h=500):UIComponent(x,y,w,h){}
		virtual ~Button();
		
		// UIComponent Identification
		virtual string getUIComponentName(){
			return "Button";
		}

	/***********************************/
	/*        	  Properties           */
	/***********************************/
	protected:
		string label;
		const string& 	getLabel(){return label;}
		void 			setLabel(const string& newLabel){label=newLabel;}
			
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	protected:
		virtual void 	initStates();
		
	/***********************************/
	/*        	    Style  			   */
	/***********************************/
	public:
		static const string FILL_COLORS_STYLE;
		static const string BORDER_COLORS_STYLE;
		static const string BORDER_SIZE_STYLE;
		static const string LABEL_COLOR_STYLE;
		static const string LABEL_ALIGN_STYLE;
		static const string CORNER_RADIUS_STYLE;
		
	protected:
		virtual void initStyles();

	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
		virtual void drawSelf();
					
	};
}

#endif /*BUTTON_H_*/
