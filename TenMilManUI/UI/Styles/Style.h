#ifndef STYLE_H_
#define STYLE_H_

#include <string>
#include <TenMilManUI/UI/Styles/StyleData/StyleData.h>

using namespace std;

namespace TenUI{
	class Style {
	protected:
		string name;
		
	public:
		Style(const string& newName)
			:name(newName){}
		virtual ~Style(){}
		
		const string& getName(){return name;}
		
		virtual void parseData(const string& newDataString) = 0;
		virtual string toString() = 0;
		
		virtual Style* clone() = 0;
	};
}

#endif /*STYLE_H_*/
