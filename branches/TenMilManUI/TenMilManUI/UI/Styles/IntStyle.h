#ifndef INTSTYLE_H_
#define INTSTYLE_H_

#include "Style.h"
#include <string>

using namespace std;

namespace TenUI{
	class IntStyle : public Style {
	protected:
		int intValue;
		
	public:
		IntStyle(const string& name, int initVal=0):intValue(initVal),Style(name){}
		int  getValue(){ return intValue; };
		void setValue(int val){ intValue = val; }
	};
}
#endif /*INTSTYLE_H_*/
