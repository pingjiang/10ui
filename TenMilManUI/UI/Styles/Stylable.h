#ifndef STYLABLE_H_
#define STYLABLE_H_

#include <string>
#include <vector>
#include <tr1/unordered_map>

#include "Style.h"

using namespace std::tr1;

namespace TenUI {
	class Stylable {
	private:
		unordered_map< string, Style*, hash<string> > styles;

		template <class StyleType>
		StyleType* getStyle(const string& name);

		template <class StyleType, typename ValueType>
		bool setStyle(const string& name, ValueType val);
		
	protected:
		bool addStyle(Style* newStyle);
		virtual void initStyles() = 0;
		
	public:
		virtual ~Stylable(){}
		
		bool setIntStyle(const string& name, int newValue);
		bool setFloatStyle(const string& name, float newValue);
		bool setStringStyle(const string& name, const string& newValue);
		bool setFloatArrayStyle(const string& name, const vector<float>& newValues);				
	};
}

#endif /*STYLABLE_H_*/
