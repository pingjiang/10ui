#ifndef STRINGSTYLE_H_
#define STRINGSTYLE_H_

#include <string>

using std::string;

namespace TenUI{
	class StringStyle : public Style {
	public:
		StringStyle(const string& initValue){ value = initValue; }
		virtual ~StringStyle(){}
		
		virtual any getValue(){
			return value;
		}
		virtual void setValue(const any& newValue){
			if(any_cast<string>(&newValue)){
				value = any_cast<string>(newValue);
			}		
		}
		virtual sp<Style> clone(){
			sp<StringStyle> newInst(new StringStyle(value));
			newInst->declaration = declaration;
			return newInst;
		}
		
	protected: 
		string value;
	};
}

#endif /*STRINGSTYLE_H_*/
