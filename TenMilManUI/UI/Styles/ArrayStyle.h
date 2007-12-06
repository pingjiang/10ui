#ifndef ARRAYSTYLE_H_
#define ARRAYSTYLE_H_

#include <string>
#include <vector>

#include <TenMilManUI/UI/Styles/StyleData/StyleData.h>

#include "Style.h"

using namespace std;

namespace TenUI{
	class ArrayStyle : public Style {
	protected:
		vector< StyleData* > array;
		StyleData* dataType;

		void stripWhiteSpace(string& in);
		bool tokenize(const string& str,
		              vector<string>& tokens);
		
		void clearArray();
		
	public:
		ArrayStyle(const string& nm, StyleData *dt, int arraySize=2);
		virtual ~ArrayStyle();
		
		StyleData* getData(unsigned int i);
				
		virtual string toString();
		virtual void parseData(const string& str);
		
		virtual Style* clone();
	};
}

#endif /*ARRAYSTYLE_H_*/
