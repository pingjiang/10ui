#ifndef STYLESETDECLARATION_H_
#define STYLESETDECLARATION_H_

#include <tr1/unordered_map>
#include <tr1/memory>
#include <map>
#include "StyleDeclaration.h"
#include "StyleSet.h"
#include "Styles/Style.h"

using std::tr1::shared_ptr;
using std::tr1::unordered_map;
using std::tr1::enable_shared_from_this;

namespace TenUI{
	
	class StyleSet;
	
	class StyleSetDeclaration : public enable_shared_from_this<StyleSetDeclaration> {
	public:
		StyleSetDeclaration(const string& _name)
			:name(_name){}
		virtual ~StyleSetDeclaration(){}
	
		void addStyleDeclaration(const shared_ptr<StyleDeclaration>& decls){
			set[decls->getName()] = decls;
		}
		void removeStyleDeclaration(const string& name){
			set.erase(name);
		}
		shared_ptr<StyleSetDeclaration> clone(){
			shared_ptr<StyleSetDeclaration> newSSDecl(new StyleSetDeclaration(name));
			for( unordered_map<string, shared_ptr<StyleDeclaration> >::iterator it = set.begin();
				 it != set.end();
				 ++it){
				newSSDecl->addStyleDeclaration(it->second);
			}
			return newSSDecl;
		}
		shared_ptr<StyleSet> createStyleSet();
		
		string getName(){
			return name;
		}
		
	private:
		unordered_map<string, shared_ptr<StyleDeclaration> > set;
		string name;
	};
	
}

#endif /*STYLESETDECLARATION_H_*/
