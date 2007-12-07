#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include "DisplayObjectContainer.h"
#include <TenMilManUI/UI/Managers/StyleManager.h>
#include <TenMilManUI/UI/Style/StyleSet.h>

#include <iostream>
#include <tr1/memory>

using namespace std;
using std::tr1::dynamic_pointer_cast;

namespace TenUI {	
	
	class UIComponent : public DisplayObjectContainer {	
	public:
		
	public:
		static std::string CLICK_EVENT;
		static std::string PRESS_EVENT;
		static std::string UNPRESS_EVENT;
		static std::string HOVER_IN_EVENT;
		static std::string HOVER_OUT_EVENT;
		static std::string HOVER_MOVE_EVENT;
		
	protected:
		shared_ptr< StyleSet > 				curStyleSet;
		shared_ptr< unordered_map< string, shared_ptr<StyleSet> >  > 	stateStyleSetMap;

		/***********************************/
		/*        Stylable Overrides       */
		/***********************************/
		virtual void initStyles();
		void loadStyleSetMap();
		
	public:
		UIComponent(int x, int y, unsigned int w=100, unsigned int h=100):DisplayObjectContainer(shared_ptr<DisplayObject>(), x,y ,w,h, 0.0,1.0,1.0){  }
		virtual ~UIComponent(){};		

		// UIComponent Identification
		virtual string getUIComponentName();
		
		
		/***********************************/
		/*        Init/Update Methods      */
		/***********************************/
		virtual void init();
		
	};
}

#endif /*UICOMPONENT_H_*/
