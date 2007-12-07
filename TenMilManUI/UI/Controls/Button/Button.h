#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Managers/StyleManager.h>

#include <iostream>
using namespace std;

namespace TenUI{

	/*##################################/
	/#        	    STYLES             #/
	/##################################*/
	namespace ButtonStyles { 
		static const string FILL_COLORS("fillColors");
		static const string BORDER_COLORS("borderColors");
		static const string BORDER_SIZE("borderSize");
		static const string LABEL_COLOR("labelColor");
		static const string LABEL_ALIGN("labelAlign");
		static const string CORNER_RADIUS("cornerRadius");
	}

	class Button : public UIComponent {
		
	/*##################################/
	/#        	    STATES             #/
	/##################################*/
	protected:
		
		
	/*##################################/
	/#        	  PROPERTIES           #/
	/##################################*/
	protected:
		string label;
		
	public:
		Button(int x, int y, unsigned int w=500, unsigned int h=500):UIComponent(x,y,w,h){}
		virtual ~Button();
		
		// UIComponent Identification
		virtual string getUIComponentName(){
			return "Button";
		}
		
		/***********************************/
		/*        Stylable Overrides       */
		/***********************************/
		virtual void initStyles();

		/************************************/
		/* DisplayObjectContainer Overrides */
		/************************************/
			/***********************************/
			/*           Draw Methods          */
			/***********************************/	
			virtual void drawSelf();
		
		/***********************************/
		/*     DisplayObject Overrides     */
		/***********************************/
			/***********************************/
			/*       Init/Update Methods       */
			/***********************************/
			virtual void update(){}
					
	};
}

#endif /*BUTTON_H_*/
