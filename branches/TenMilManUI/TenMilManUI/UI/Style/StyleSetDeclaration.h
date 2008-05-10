#ifndef STYLESETDECLARATION_H_
#define STYLESETDECLARATION_H_

#include <map>
#include <tr1/unordered_map>

#include <TenMilManUI/Util/SmartPointer.h>

#include "StyleDeclaration.h"
#include "StyleSet.h"
#include "Styles/Style.h"

using std::tr1::unordered_map;

namespace TenUI{
	
	class StyleSet;
	
	class StyleSetDeclaration : public enable_shared_from_this<StyleSetDeclaration> {
	public:
		StyleSetDeclaration(const string& _name)
			:name(_name){}
		virtual ~StyleSetDeclaration(){}

		void addStyleDeclaration(const sp<StyleDeclaration>& decls){
			set[decls->getName()] = decls;
		}
		void setStyleDeclaration(const sp<StyleDeclaration>& decls){
			set[decls->getName()] = decls;
		}
		void removeStyleDeclaration(const string& name){
			set.erase(name);
		}
		sp<StyleSetDeclaration> clone(){
			sp<StyleSetDeclaration> newSSDecl(new StyleSetDeclaration(name));
			for( unordered_map<string, sp<StyleDeclaration> >::iterator it = set.begin();
				 it != set.end();
				 ++it){
				newSSDecl->addStyleDeclaration(it->second);
			}
			return newSSDecl;
		}
		sp<StyleSet> createStyleSet();
		
		string getName(){
			return name;
		}
		
	private:
		unordered_map<string, sp<StyleDeclaration> > set;
		string name;
	};
	
}

#endif /*STYLESETDECLARATION_H_*/
