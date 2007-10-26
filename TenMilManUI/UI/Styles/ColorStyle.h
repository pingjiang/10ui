#ifndef COLORSTYLE_H_
#define COLORSTYLE_H_

#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include "Style.h"

namespace TenUI {
	class ColorStyle : public Style {
	protected:
		ColorHex ch;
		
	public:
		ColorStyle(const string& name, const ColorHex& initVal):ch(initVal),Style(name){}
				
		const ColorHex& getValue(){ return ch; };
		void setValue(const ColorHex& val){ ch = val; }
	};
}

#endif /*COLORSTYLE_H_*/
