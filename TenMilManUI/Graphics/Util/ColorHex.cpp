#include "ColorHex.h"

namespace TenUI{
	const ColorHex ColorHex::NoColor(0,0,0,0);
	
	ostream& operator <<(ostream& os, ColorHex& ch){
		return os<<ch.toString();
	}
}
