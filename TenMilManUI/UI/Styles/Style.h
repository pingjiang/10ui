#ifndef STYLE_H_
#define STYLE_H_

#include <string>

using namespace std;

namespace TenUI{
	class Style {
	protected:
		string name;
		
	public:
		Style(const string& newName):name(newName){}
		virtual ~Style(){}
		
		const string& getName(){return name;}
	};
}

#endif /*STYLE_H_*/
