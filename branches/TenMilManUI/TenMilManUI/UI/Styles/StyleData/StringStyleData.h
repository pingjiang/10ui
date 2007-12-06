#ifndef STRINGSTYLEDATA_H_
#define STRINGSTYLEDATA_H_

#include "StyleData.h"

namespace TenUI {
	
	class StringStyleData : public StyleData {
	protected:
		string stringValue;
		
	public:
		StringStyleData(){
			stringValue = "";
		}
		StringStyleData(const string& val){
			stringValue = val;
		}
		virtual ~StringStyleData(){}
		
		virtual bool isSameType(StyleData* a){
			return (dynamic_cast< StringStyleData* >(a) != NULL);			
		}
		virtual StyleData* clone(){
			return new StringStyleData(stringValue);
		}
		
		virtual void setValue(const string& newValue){ 
			stringValue = newValue; 
		}
		const string& getValue(){
			return stringValue;
		}
		
		virtual void parseData(const string& stringData){
			stringValue = stringData;
		}
		virtual string toString(){
			return stringValue;
		}
	};

}

#endif /*STRINGSTYLEDATA_H_*/
