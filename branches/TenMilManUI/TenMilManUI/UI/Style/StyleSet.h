#ifndef STYLESET_H_
#define STYLESET_H_

#include <boost/any.hpp>
#include <string>
#include <tr1/unordered_map>

#include <TenMilManUI/Util/SmartPointer.h>

#include "Styles/Style.h"
#include "StyleDeclaration.h"
#include "StyleSetDeclaration.h"

using boost::any;
using std::string;
using std::tr1::unordered_map;

namespace TenUI{
	
	class StyleSetDeclaration;
	
	class StyleSet {
	public:
		StyleSet(const sp<StyleSetDeclaration>& _declaration, 
				 const sp< unordered_map<string, sp<Style> > >& _styleMap)
			:declaration(_declaration),
			 styleMap(_styleMap){}
		virtual ~StyleSet(){}
		
		sp<Style>	getStyle(const string& styleName){
			return (*styleMap)[styleName];
		}
		any getValue(const string& styleName){
			unordered_map< string, sp<Style> >::iterator it = styleMap->find(styleName);
			if(it != styleMap->end()){
				return it->second->getValue();
			}
			return any();
		}
		void setValue(const string& styleName, const any& newValue){
			unordered_map< string, sp<Style> >::iterator it = styleMap->find(styleName);
			if(it != styleMap->end()){
				it->second->setValue(newValue);
			}
		}
		sp<StyleSet> clone();
		string getName();
			
	private: 
		sp<StyleSetDeclaration> declaration;
		sp< unordered_map<string, sp<Style> > > styleMap;
	};
	
}

#endif /*STYLESET_H_*/
