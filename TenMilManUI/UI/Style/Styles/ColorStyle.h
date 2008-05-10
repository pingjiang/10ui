#ifndef COLORSTYLE_H_
#define COLORSTYLE_H_

#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include <string>

using std::string;

namespace TenUI{
	class ColorStyle : public Style {
	public:
		ColorStyle(const ColorHex& initValue){ value = initValue; }
		ColorStyle(const string& initValue){ value.setColor(initValue); }
		virtual ~ColorStyle(){}
		
		virtual any getValue(){
			return value;
		}
		virtual void setValue(const any& newValue){
			
			const string* svalue = any_cast<string>(&newValue);
			if(svalue){
				value.setColor(*svalue);
				return;
			}
			

			const ColorHex* cvalue = any_cast<ColorHex>(&newValue);
			if(cvalue){
				value = (*cvalue);
				return;
			}
		}
		virtual sp<Style> clone(){
			sp<ColorStyle> newInst(new ColorStyle(value));
			newInst->declaration = declaration;
			return newInst;
		}
		
	protected: 
		ColorHex value;
	};
}

#endif /*COLORSTYLE_H_*/
