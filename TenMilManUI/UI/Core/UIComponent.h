#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"
#include <TenMilManUI/UI/Styles/Stylable.h>

#include <iostream>
using namespace std;

namespace TenUI {	
	
	class UIComponent : public DisplayObjectContainer, public Stylable {
	public:
		static std::string CLICK_EVENT;
		static std::string PRESS_EVENT;
		static std::string UNPRESS_EVENT;
		static std::string HOVER_IN_EVENT;
		static std::string HOVER_OUT_EVENT;
		static std::string HOVER_MOVE_EVENT;
		
	public:
		UIComponent(int x, int y, unsigned int w=100, unsigned int h=100):DisplayObjectContainer(NULL, x,y ,w,h, 0.0,1.0,1.0){ cout << "UIComponent(x,y):" << x << "," << y << endl; }
		virtual ~UIComponent(){};		

		/***********************************/
		/*        Stylable Overrides       */
		/***********************************/
		virtual void initStyles();
		
		/***********************************/
		/*        Init/Update Methods      */
		/***********************************/
		virtual void init();
		
	};
}

#endif /*UICOMPONENT_H_*/
