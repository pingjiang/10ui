#include "StyleSetDeclaration.h"	
namespace TenUI{

	sp<StyleSet> StyleSetDeclaration::createStyleSet(){
		sp< unordered_map<string, sp<Style> > > newStyleMap( new unordered_map<string, sp<Style> >() );
		for( unordered_map<string, sp<StyleDeclaration> >::iterator it = set.begin(); 
			 it != set.end();
			 ++it){
			sp<Style> newStyle = it->second->createStyle();
			(*newStyleMap)[newStyle->getName()] = newStyle;
		}
		
		return sp<StyleSet> (new StyleSet(shared_from_this(), newStyleMap));
	}
	
}
