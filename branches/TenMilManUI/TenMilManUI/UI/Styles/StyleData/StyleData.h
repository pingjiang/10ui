#ifndef STYLEDATA_H_
#define STYLEDATA_H_

#include <string>
using namespace std;

namespace TenUI {
	
	class StyleData {
	public:
		virtual ~StyleData(){}
		
		virtual bool isSameType(StyleData* a) = 0;
		virtual StyleData* clone() = 0;
		
		virtual void parseData(const string& stringData) = 0;
		virtual string toString() = 0;
	};

}

#endif /*STYLEDATA_H_*/
