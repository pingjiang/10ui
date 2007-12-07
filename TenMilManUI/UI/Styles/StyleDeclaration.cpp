#include "StyleDeclaration.h"


	shared_ptr<StyleDeclaration> StyleDeclaration::create(const string& _name, const shared_ptr<Style>& _defaultStyle){
		shared_ptr<StyleDeclaration> newDecl(new StyleDeclaration(_name, _defaultStyle));
		_defaultStyle->declaration = newDecl;
		return newDecl;
	}

	StyleDeclaration::StyleDeclaration(const string& _name, const shared_ptr<Style>& _defaultStyle)
		:name(_name){
		 defaultStyle = _defaultStyle;
	}
	
	shared_ptr<Style>	StyleDeclaration::createStyle(){
		return defaultStyle->clone();
	}

