#ifndef GRADIENTSTYLE_H_
#define GRADIENTSTYLE_H_

#include <vector>
#include "Style.h"

using namespace std;

namespace TenUI {
	class GradientStyle : public Style {		
	protected:
		vector<ColorHex> chs;
		
	public:
		GradientStyle(const string& name, const vector<ColorHex>& initVal=vector<ColorHex>()):chs(initVal),Style(name){}
		GradientStyle(const string& name, const ColorHex& oneColor):Style(name){
			setOneColor(oneColor);
		}
		GradientStyle(const string& name, const ColorHex& oneColor, const ColorHex& twoColor):Style(name){
			setTwoColor(oneColor, twoColor);
		}
				
		const vector<ColorHex>& getValue(){ return chs; };
		void setValue(const vector<ColorHex>& val){ chs = val; }
		
		int getNumColors(){
			return chs.size();
		}
		
		void setOneColor(const ColorHex& color){
			chs.clear();
			chs.push_back(color);
		}		
		void setTwoColor(const ColorHex& color1, const ColorHex& color2){
			chs.clear();
			chs.push_back(color1);
			chs.push_back(color2);
		}	
	};
}


#endif /*GRADIENTSTYLE_H_*/
