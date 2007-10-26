#ifndef FLOATSTYLE_H_
#define FLOATSTYLE_H_

#include "Style.h"
#include <string>

using namespace std;

namespace TenUI{
	class FloatArrayStyle : Style {
	protected:
		vector<float> floatValues;
		
	public:
		FloatArrayStyle(const string& name, const vector<float>& initVal=vector<float>()):floatValues(initVal),Style(name){}
		
		unsigned int getSize(){return floatValues.size();}
		
		const vector<float>& getValue(){ return floatValues; };
		void setValue(const vector<float>&val){ floatValues = val; }
	};
}
#endif /*INTSTYLE_H_*/
