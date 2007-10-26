#ifndef STRINGSTYLE_H_
#define STRINGSTYLE_H_

#include "Style.h"
#include <string>

using namespace std;

namespace TenUI{
	class StringStyle : Style {
	protected:
		string stringValue;
		
	public:
		StringStyle(const string& name, const string& initVal=string()):stringValue(initVal),Style(name){}
		const string& getValue(){ return stringValue; };
		void setValue(const string& val){ stringValue = val; }
	};
}
#endif /*INTSTYLE_H_*/
