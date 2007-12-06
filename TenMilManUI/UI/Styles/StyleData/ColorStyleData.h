#ifndef COLORSTYLEDATA_H_
#define COLORSTYLEDATA_H_

#include <TenMilManUI/Graphics/Util/ColorHex.h>
#include "StyleData.h"

namespace TenUI {
	
	class ColorStyleData : public StyleData {
	protected:
		ColorHex color;				
	
	public:
		ColorStyleData(){
			color = ColorHex::NoColor;
		}
		ColorStyleData(const ColorHex& c){
			color = c;
		}		
		virtual ~ColorStyleData(){}
		
		virtual bool isSameType(StyleData* a){
			return (dynamic_cast< ColorStyleData* >(a) != NULL);
		}
		virtual StyleData* clone(){
			return new ColorStyleData(color);
		}
		
		void setValue(const ColorHex& newValue){ 
			color = newValue; 
		}
		const ColorHex& getValue(){
			return color;
		}
		
		void parseData(const string& stringData){
			color.setColor(stringData);
		}
		virtual string toString(){
			return color.toString();
		}
	};

}

#endif /*COLORSTYLEDATA_H_*/
