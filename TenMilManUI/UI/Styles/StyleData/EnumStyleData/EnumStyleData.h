#ifndef ENUMSTYLEDATA_H_
#define ENUMSTYLEDATA_H_

#include <string>
#include <tr1/unordered_set>

#include "../StyleData.h"

using namespace std;
using namespace std::tr1;

namespace TenUI {
	
	class EnumStyleData : public StyleData {
	protected:
		string value;
		unordered_set< string, hash<string> > enumSet;
		string defaultValue;
		
	public:
		EnumStyleData(){}
		EnumStyleData(const unordered_set< string, hash<string> >& eset, const string& def){
			defaultValue = value = def;
			enumSet = eset;
		}
		virtual ~EnumStyleData(){}
		
		virtual bool isSameType(StyleData* a){
			return (dynamic_cast< EnumStyleData* >(a) != NULL);
		}
		virtual StyleData* clone(){
			return new EnumStyleData(enumSet, defaultValue);
		}
		
		virtual void setValue(const string& newValue){
			unordered_set<string>::iterator it = enumSet.find(newValue);
			if(it != enumSet.end()){
				value = newValue;
			}
		}
		virtual const string& getValue(){
			return value;
		}
		
		virtual void parseData(const string& stringData){
			setValue(stringData);
		}
		virtual string toString(){
			return value;
		}
	};

}

#endif /*STRINGSTYLEDATA_H_*/
