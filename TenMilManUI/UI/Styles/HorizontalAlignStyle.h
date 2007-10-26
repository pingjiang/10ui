#ifndef HORIZONTALALIGNSTYLE_H_
#define HORIZONTALALIGNSTYLE_H_

#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include "Style.h"

namespace TenUI {
	namespace HorizontalAlignOptions {
		
		enum HorizontalAlignOptions_enum {LEFT=1, CENTER, RIGHT};
	}
	class HorizontalAlignStyle : public Style {
	protected:
		HorizontalAlignOptions::HorizontalAlignOptions_enum alignOpt;
		
	public:
		HorizontalAlignStyle(const string& name, HorizontalAlignOptions::HorizontalAlignOptions_enum initVal= HorizontalAlignOptions::LEFT):alignOpt(initVal),Style(name){}
				
		HorizontalAlignOptions::HorizontalAlignOptions_enum getValue(){ return alignOpt; };
		void setValue(HorizontalAlignOptions::HorizontalAlignOptions_enum val){ alignOpt = val; }
	};
		
}

#endif /*COLORSTYLE_H_*/
