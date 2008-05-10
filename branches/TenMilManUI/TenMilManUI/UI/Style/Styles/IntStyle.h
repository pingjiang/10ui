#ifndef INTSTYLE_H_
#define INTSTYLE_H_

#include "Style.h"

namespace TenUI{
	class IntStyle : public Style {
	public:
		IntStyle(int initValue){ value = initValue; }
		virtual ~IntStyle(){}
		
		virtual any getValue(){
			return value;
		}
		virtual void setValue(const any& newValue){
			if(newValue.type() == typeid(int)){
				value = any_cast<int>(newValue);
			}
		}	
		virtual sp<Style> clone(){
			sp<IntStyle> newInst(new IntStyle(value));
			newInst->declaration = declaration;
			return newInst;
		}
		
	protected: 
		int value;
	};
}

#endif /*INTSTYLE_H_*/
