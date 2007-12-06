#ifndef STYLESET_H_
#define STYLESET_H_

#include <string>
#include <vector>
#include <tr1/unordered_map>

#include <TenMilManUI/Graphics/Util/ColorHex.h>

#include "Style.h"
#include "SingleStyle.h"
#include "ArrayStyle.h"

using namespace std;
using namespace std::tr1;

namespace TenUI {

	class StyleSet {
	private:
		string name;
		unordered_map< string, SingleStyle*, hash<string> > single_styles;
		unordered_map< string, ArrayStyle*, hash<string> > array_styles;
		
		/******************************
		 * SingleStyle Helper methods *
		 ******************************/
		template <class StyleDataType>
		StyleDataType* getStyleData(const string& name);
				
		template <class StyleDataType, typename ValueType>
		ValueType getStyleDataValue(const string& name);

		template <class StyleDataType, typename ValueType>
		void setStyleDataValue(const string& name, ValueType val);

		/*****************************
		 * ArrayStyle Helper methods *
		 *****************************/
		template <class StyleDataType>
		StyleDataType* getArrayStyleData(const string& name, unsigned int i);
		
		template <class StyleDataType, typename ValueType>
		ValueType getArrayStyleDataValue(const string& name, unsigned int i);
		
		template <class StyleDataType, typename ValueType>
		void setArrayStyleDataValue(const string& name, unsigned int i, ValueType val);
		
	public:
		StyleSet(const string& nm);
		virtual ~StyleSet(){}

		const string& 	getName();
		
		bool 			addStyle(Style* newStyle);
		
		string 			toString();
		void			parseString(const string&);
		
		StyleSet*		clone(const string&);
		
		/***********************
		 * SingleStyle methods *
		 ***********************/
		int   			getIntStyle(	const string& name);
		float 			getFloatStyle(	const string& name);
		const ColorHex& getColorStyle(	const string& name);
		const string& 	getEnumStyle(	const string& name);
		const string& 	getStringStyle(	const string& name);

		void setIntStyle(const string& name, int newValue);
		void setFloatStyle(const string& name, float newValue);
		void setColorStyle(const string& name, const ColorHex& newValue);
		void setEnumStyle(const string& name, const string& newValue);
		void setStringStyle(const string& name, const string& newValue);
				
		/**********************
		 * ArrayStyle methods *
		 **********************/ 
		int   			getArrayIntStyle(	const string& name, unsigned int i);
		float			getArrayFloatStyle(	const string& name, unsigned int i);
		const ColorHex& getArrayColorStyle(	const string& name, unsigned int i);
		const string& 	getArrayEnumStyle(	const string& name, unsigned int i);
		const string& 	getArrayStringStyle(const string& name, unsigned int i);

		void setArrayIntStyle(	 const string& name, unsigned int i, int newValue);
		void setArrayFloatStyle( const string& name, unsigned int i, float newValue);
		void setArrayColorStyle( const string& name, unsigned int i, const ColorHex& newValue);
		void setArrayEnumStyle(	 const string& name, unsigned int i, const string& newValue);
		void setArrayStringStyle(const string& name, unsigned int i, const string& newValue);
	};
}

#endif /*STYLESET_H_*/
