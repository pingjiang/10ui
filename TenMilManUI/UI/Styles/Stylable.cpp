#include "Stylable.h"

#include "IntStyle.h"
#include "FloatStyle.h"
#include "FloatArrayStyle.h"
#include "ObjectStyle.h"
#include "StringStyle.h"

namespace TenUI {

	bool Stylable::addStyle(Style* newStyle){
		unordered_map<string, Style*>::iterator it = styles.find(newStyle->getName());
		if(it == styles.end()){
			styles[newStyle->getName()] = newStyle;
			return true;
		}
		return false;
	}
	
	template <class StyleType>
	StyleType* Stylable::getStyle(const string& name){
		unordered_map<string, Style*>::iterator it = styles.find(name);
		if(it != styles.end()){
			return dynamic_cast<StyleType* >(it->second);
		}
		return NULL;
	}
	

	template <class StyleType, typename ValueType>
	bool Stylable::setStyle(const string& name, ValueType val){
		StyleType* style = getStyle<StyleType>(name);
		if(style != NULL){
			style->setValue(val);
			return true;
		}
		return false;
	}

	bool Stylable::setIntStyle(const string& name, int newValue){
		return setStyle<IntStyle, int>(name, newValue);
	}
	bool Stylable::setFloatStyle(const string& name, float newValue){
		return setStyle<FloatStyle, float>(name, newValue);
	}
	bool Stylable::setStringStyle(const string& name, const string& newValue){
		return setStyle<StringStyle, const string&>(name, newValue);
	}
	bool Stylable::setFloatArrayStyle(const string& name, const vector<float>& newValues){
		return setStyle<FloatArrayStyle, const vector<float>& >(name, newValues);
	}	
	
}
