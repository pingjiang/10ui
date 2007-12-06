#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>

#include <TenMilManUI/UI/Styles/StyleData/ColorStyleData.h>
#include <TenMilManUI/UI/Styles/StyleData/EnumStyleData/HorizontalAlignStyleData.h>
#include <TenMilManUI/UI/Styles/StyleData/IntStyleData.h>

#include <iostream>
using namespace std;

namespace TenUI{

	namespace ButtonStyles { 
		static const string FILL_COLORS("fillColors");
		static const string BORDER_COLORS("borderColors");
		static const string BORDER_SIZE("borderColors");
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
	/#        	    STYLES             #/
	/##################################*/
	protected:
		/*ColorStyleData* 			fillColor1_style;
		ColorStyleData* 			fillColor2_style;
		
		ColorStyleData* 			borderColor1_style;
		ColorStyleData* 			borderColor2_style;
				
		IntStyleData*				borderSize_style;
		
		ColorStyleData* 			labelColor_style;
		HorizontalAlignStyleData*	labelAlign_style;
		
		IntStyleData*				cornerRadius_style;*/
		
		ColorHex	fillColor1_style;
		ColorHex 	fillColor2_style;
		
		ColorHex 	borderColor1_style;
		ColorHex 	borderColor2_style;
				
		int			borderSize_style;
		
		ColorHex 	labelColor_style;
		int			labelAlign_style;
		
		int			cornerRadius_style;
	
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
