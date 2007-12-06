#ifndef INTSTYLEDATA_H_
#define INTSTYLEDATA_H_

#include "StyleData.h"

#include <sstream>
using namespace std;

namespace TenUI {
	
	class IntStyleData : public StyleData {
	protected:
		int intValue;
				
		int stringToInt(const string& sval){
			int result = 0;
			istringstream s1;
			s1.str(sval);
			s1 >> result;

			if( s1.bad() ){
				return 0;
			}
			return result;
		}
		
		string intToString(int val){
			ostringstream s1;
			s1 << val;
			if( s1.bad() ){
				return "0";
			}
			return s1.str();			
		}

	public:
		IntStyleData(){
			intValue = 0;
		}
		IntStyleData(int val){
			intValue = val;
		}
		virtual ~IntStyleData(){}
		
		virtual bool isSameType(StyleData* a){
			return (dynamic_cast< IntStyleData* >(a) != NULL);
		}
		virtual StyleData* clone(){
			return (StyleData*) new IntStyleData(intValue);
		}
		
		virtual void setValue(int newValue){ 
			intValue = newValue; 
		}
		virtual int getValue(){
			return intValue;
		}
		
		virtual void parseData(const string& stringData){
			intValue = stringToInt(stringData);
		}
		virtual string toString(){
			return intToString(intValue);
		}
	};

}

#endif /*INTSTYLEDATA_H_*/
