#ifndef FLOATARRAYSTYLE_H_
#define FLOATARRAYSTYLE_H_

#include "Style.h"
#include <string>
#include <vector>

using namespace std;

namespace TenUI{

	class FloatStyle : Style {
	protected:
		float floatValue;
		
	public:
		FloatStyle(const string& name, float initVal=0.0):floatValue(initVal),Style(name){}
		float getValue(){ return floatValue; };
		void setValue(float val){ floatValue = val; }
	};

}
#endif /*INTSTYLE_H_*/
