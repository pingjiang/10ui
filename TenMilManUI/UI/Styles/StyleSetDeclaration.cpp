#include "StyleSetDeclaration.h"	

	shared_ptr<StyleSet> StyleSetDeclaration::createStyleSet(){
		shared_ptr< unordered_map<string, shared_ptr<Style> > > newStyleMap( new unordered_map<string, shared_ptr<Style> >() );
		for( unordered_map<string, shared_ptr<StyleDeclaration> >::iterator it = set.begin(); 
			 it != set.end();
			 ++it){
			shared_ptr<Style> newStyle = it->second->createStyle();
			(*newStyleMap)[newStyle->getName()] = newStyle;
		}
		
		return shared_ptr<StyleSet> (new StyleSet(shared_from_this(), newStyleMap));
	}
