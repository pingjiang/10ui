#ifndef STYLESET_H_
#define STYLESET_H_

#include <boost/any.hpp>
#include <string>
#include <tr1/memory>
#include <tr1/unordered_map>

#include "Styles/Style.h"
#include "StyleDeclaration.h"
#include "StyleSetDeclaration.h"

using boost::any;
using std::string;
using std::tr1::shared_ptr;
using std::tr1::unordered_map;

namespace TenUI{
	
	class StyleSetDeclaration;
	
	class StyleSet {
	public:
		StyleSet(const shared_ptr<StyleSetDeclaration>& _declaration, 
				 const shared_ptr< unordered_map<string, shared_ptr<Style> > >& _styleMap)
			:declaration(_declaration),
			 styleMap(_styleMap){}
		virtual ~StyleSet(){}
		
		shared_ptr<Style>	getStyle(const string& styleName){
			return (*styleMap)[styleName];
		}
		any getValue(const string& styleName){
			unordered_map< string, shared_ptr<Style> >::iterator it = styleMap->find(styleName);
			if(it != styleMap->end()){
				return it->second->getValue();
			}
			return any();
		}
		void setValue(const string& styleName, const any& newValue){
			unordered_map< string, shared_ptr<Style> >::iterator it = styleMap->find(styleName);
			if(it != styleMap->end()){
				it->second->setValue(newValue);
			}
		}
		
		string getName();
			
	private: 
		shared_ptr<StyleSetDeclaration> declaration;
		shared_ptr< unordered_map<string, shared_ptr<Style> > > styleMap;
	};
	
}

#endif /*STYLESET_H_*/
