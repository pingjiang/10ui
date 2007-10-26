#ifndef OBJECTSTYLE_H_
#define OBJECTSTYLE_H_

#include "Style.h"
#include <string>
#include <vector>

using namespace std;

namespace TenUI{
	class ObjectStyle : Style {
	protected:
		void* objValue;
		
	public:
		ObjectStyle(const string& name, void* initVal=NULL):objValue(initVal),Style(name){}
		
		void* getValue(){ return objValue; };
		void setValue(void* val){ objValue = val; }
	};
}
#endif /*INTSTYLE_H_*/
