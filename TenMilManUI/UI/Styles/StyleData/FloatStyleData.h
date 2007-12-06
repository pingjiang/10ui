#ifndef FLOATSTYLEDATA_H_
#define FLOATSTYLEDATA_H_

#include "StyleData.h"
#include <sstream>

using namespace std;

namespace TenUI {
	
	class FloatStyleData : public StyleData {
	protected:
		float floatValue;
				
		float stringToFloat(const string& sval){
			float result = 0;
			istringstream s1;
			s1.str(sval);
			s1 >> result;
			
			if( s1.bad() ){
				return 0;
			}
			return result;
		}
		
		string floatToString(float val){
			ostringstream s1;
			s1 << val;
			if( s1.bad() ){
				return "0";
			}
			return s1.str();			
		}

	public:
		FloatStyleData(){
			floatValue = 0.0;
		}
		FloatStyleData(float val){
			floatValue = val;
		}		
		virtual ~FloatStyleData(){}
		
		virtual bool isSameType(StyleData* a){
			return (dynamic_cast< FloatStyleData* >(a) != NULL);
		}
		virtual StyleData* clone(){
			new FloatStyleData(floatValue);
		}
		
		virtual void setValue(float newValue){ 
			floatValue = newValue; 
		}
		virtual float getValue(){
			return floatValue;
		}
		
		virtual void parseData(const string& stringData){
			floatValue = stringToFloat(stringData);
		}
		virtual string toString(){
			return floatToString(floatValue);
		}
	};

}

#endif /*FLOATSTYLEDATA_H_*/
