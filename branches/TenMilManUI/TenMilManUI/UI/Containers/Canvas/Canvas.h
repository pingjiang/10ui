#ifndef CANVAS_H_
#define CANVAS_H_

#include <string>

#include <TenMilManUI/UI/Core/UIComponent.h>
#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include <TenMilManUI/UI/Managers/StyleManager.h>

#include <iostream>

#include <TenMilManUI/Graphics/IImage.h>

using std::cout;
using std::endl;

namespace TenUI{

	class Canvas : public UIComponent {
	public:
		Canvas(int x, int y, unsigned int w=500, unsigned int h=500):UIComponent(x,y,w,h){}
		virtual ~Canvas();
		
		// UIComponent Identification
		virtual string getUIComponentName(){
			return "Canvas";
		}

	/***********************************/
	/*        	  Properties           */
	/***********************************/
	protected:
		/*string label;
		const string& 	getLabel(){return label;}
		void 			setLabel(const string& newLabel){label=newLabel;}*/
		IImage* image;
			
	/***********************************/
	/*          State Machine  		   */
	/***********************************/
	protected:
		//virtual void 	initStates();
		
	/***********************************/
	/*        	    Style  			   */
	/***********************************/
	public:
		static const string BACKGROUND_IMAGE;
		static const string BACKGROUND_COLOR;
		
	protected:
		virtual void initStyles();

	/***********************************/
	/*        Game Loop Methods        */
	/***********************************/
	public:
		virtual void init();
		virtual void drawSelf();
					
	};
}

#endif /*BUTTON_H_*/
