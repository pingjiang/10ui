#include "StyleSet.h"

#include "StyleData/StringStyleData.h"
#include "StyleData/IntStyleData.h"
#include "StyleData/FloatStyleData.h"
#include "StyleData/EnumStyleData/EnumStyleData.h"
#include "StyleData/ColorStyleData.h"

namespace TenUI {

	StyleSet::StyleSet(const string& nm):name(nm){}

	const string& StyleSet::getName(){
		return name;
	}
	
	StyleSet* StyleSet::clone(const string& newName){
		StyleSet* cloned = new StyleSet(newName);
		
		unordered_map< string, SingleStyle*>::iterator singleit = single_styles.begin();
		while(singleit != single_styles.end()){
			cloned->addStyle(singleit->second->clone());
		}
		
		unordered_map< string, ArrayStyle*>::iterator arrayit = array_styles.begin();
		while(arrayit != array_styles.end()){
			cloned->addStyle(arrayit->second->clone());
		}
		
		return cloned;
	}
	
	//TODO implement StyleSet::toString
	string 	StyleSet::toString(){return "";}
	//TODO implement StyleSet::parseString
	void	StyleSet::parseString(const string&){}

	bool StyleSet::addStyle(Style* newStyle){
		// SingleStyle
		SingleStyle* sstyle = dynamic_cast< SingleStyle* >(newStyle);
		if(sstyle != NULL){
			unordered_map<string, SingleStyle*>::iterator it = single_styles.find(sstyle->getName());
			if(it == single_styles.end()){
				single_styles[sstyle->getName()] = sstyle;
				return true;
			}
		}else{	
			// ArrayStyle
			ArrayStyle* astyle = dynamic_cast< ArrayStyle* >(newStyle);
			if(astyle != NULL){
				unordered_map<string, ArrayStyle*>::iterator it = array_styles.find(astyle->getName());
				if(it == array_styles.end()){
					array_styles[astyle->getName()] = astyle;
					return true;
				}
			}		
		}
		
		return false;
	}

	template <class StyleDataType>
	StyleDataType* StyleSet::getStyleData(const string& name){
		unordered_map<string, SingleStyle*>::iterator it = single_styles.find(name);
		if(it != single_styles.end()){
			SingleStyle* s = it->second;
			StyleDataType* sdata =  dynamic_cast< StyleDataType* >(s->getData());
			return sdata;
		}
		return NULL;
	}
	
	template <class StyleDataType>
	StyleDataType* StyleSet::getArrayStyleData(const string& name, unsigned int i){
		unordered_map<string, ArrayStyle*>::iterator it = array_styles.find(name);
		if(it != array_styles.end()){
			ArrayStyle* s = it->second;
			StyleDataType* sdata =  dynamic_cast< StyleDataType* >(s->getData(i));
			return sdata;
		}
		return NULL;
	}
	
	template <class StyleDataType, typename ValueType>
	ValueType StyleSet::getStyleDataValue(const string& name){
		StyleDataType* sdata =  getStyleData<StyleDataType>(name);
		if(sdata != NULL){ return sdata->getValue(); }
	}
	
	template <class StyleDataType, typename ValueType>
	void StyleSet::setStyleDataValue(const string& name, ValueType val){
		StyleDataType* sdata = getStyleData<StyleDataType>(name);
		if(sdata != NULL){ sdata->setValue(val); }
	}

	template <class StyleDataType, typename ValueType>
	ValueType StyleSet::getArrayStyleDataValue(const string& name, unsigned int i){
		StyleDataType* sdata =  getArrayStyleData<StyleDataType>(name, i);
		if(sdata != NULL){ return sdata->getValue(); }
	}
	
	template <class StyleDataType, typename ValueType>
	void StyleSet::setArrayStyleDataValue(const string& name, unsigned int i, ValueType val){
		StyleDataType* sdata = getArrayStyleData<StyleDataType>(name, i);
		if(sdata != NULL){ sdata->setValue(val); }
	}	
	
	
	int StyleSet::getIntStyle(const string& name){
		return getStyleDataValue<IntStyleData, int>(name);
	}
	float StyleSet::getFloatStyle(const string& name){
		return getStyleDataValue<FloatStyleData, float>(name);
	}
	const ColorHex& StyleSet::getColorStyle(const string& name){
		return getStyleDataValue<ColorStyleData, const ColorHex&>(name);
	}
	const string& StyleSet::getEnumStyle(const string& name){
		return getStyleDataValue<EnumStyleData, const string&>(name);
	}	
	const string& StyleSet::getStringStyle(const string& name){
		return getStyleDataValue<StringStyleData, const string&>(name);
	}
	

	void StyleSet::setIntStyle(const string& name, int newValue){
		setStyleDataValue< IntStyleData, int > (name, newValue);
	}
	void StyleSet::setFloatStyle(const string& name, float newValue){
		setStyleDataValue<FloatStyleData, float>(name, newValue);
	}
	void StyleSet::setColorStyle(const string& name, const ColorHex& newValue){
		setStyleDataValue<ColorStyleData, const ColorHex&>(name, newValue);
	}
	void StyleSet::setEnumStyle(const string& name, const string& newValue){
		setStyleDataValue<EnumStyleData, const string&>(name, newValue);
	}	
	void StyleSet::setStringStyle(const string& name, const string& newValue){
		setStyleDataValue<StringStyleData, const string&>(name, newValue);
	}
	

	int   			StyleSet::getArrayIntStyle(	const string& name, unsigned int i){
		return getArrayStyleDataValue<IntStyleData, int>(name, i);
	}
	float			StyleSet::getArrayFloatStyle(	const string& name, unsigned int i){
		return getArrayStyleDataValue<FloatStyleData, float>(name, i);
	}
	const ColorHex& StyleSet::getArrayColorStyle(	const string& name, unsigned int i){
		return getArrayStyleDataValue<ColorStyleData, const ColorHex&>(name, i);
	}
	const string& 	StyleSet::getArrayEnumStyle(	const string& name, unsigned int i){
		return getArrayStyleDataValue<EnumStyleData, const string&>(name, i);
	}
	const string& 	StyleSet::getArrayStringStyle(	const string& name, unsigned int i){
		return getArrayStyleDataValue<StringStyleData, const string&>(name, i);
	}

	void StyleSet::setArrayIntStyle(	const string& name, unsigned int i, int newValue){
		setArrayStyleDataValue<IntStyleData, int&>(name, i, newValue);
	}
	void StyleSet::setArrayFloatStyle(	const string& name, unsigned int i, float newValue){
		setArrayStyleDataValue<FloatStyleData, float>(name, i, newValue);
	}
	void StyleSet::setArrayColorStyle( const string& name, unsigned int i, const ColorHex& newValue){
		setArrayStyleDataValue<ColorStyleData, const ColorHex&>(name, i, newValue);
	}
	void StyleSet::setArrayEnumStyle(	const string& name, unsigned int i, const string& newValue){
		setArrayStyleDataValue<EnumStyleData, const string&>(name, i, newValue);
	}
	void StyleSet::setArrayStringStyle(const string& name, unsigned int i, const string& newValue){
		setArrayStyleDataValue<StringStyleData, const string&>(name, i, newValue);
	}
	
}
