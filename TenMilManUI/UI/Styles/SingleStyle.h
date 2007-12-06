#ifndef SINGLESTYLE_H_
#define SINGLESTYLE_H_

#include <string>

#include <TenMilManUI/UI/Styles/StyleData/StyleData.h>
#include "Style.h"

using namespace std;

namespace TenUI{
	class SingleStyle : public Style {
	protected:
		StyleData* data;
		
	public:
		SingleStyle(const string& newName, StyleData* newData)
			:Style(newName),
			data(newData){}
		virtual ~SingleStyle(){ delete data; }
		
		StyleData* getData(){return data;}
	
		virtual string toString(){ return name +": "+ data->toString(); } 
		virtual void parseData(const string& newDataString){
			if(data != NULL){
				data->parseData(newDataString);
			}
		}
		
		virtual Style* clone(){
			return new SingleStyle(name, data->clone());
		}
	};
}

#endif /*SINGLESTYLE_H_*/
