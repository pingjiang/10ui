#include "StyleDeclaration.h"
namespace TenUI{

	sp<StyleDeclaration> StyleDeclaration::create(const string& _name, const sp<Style>& _defaultStyle){
		sp<StyleDeclaration> newDecl(new StyleDeclaration(_name, _defaultStyle));
		_defaultStyle->declaration = newDecl;
		return newDecl;
	}

	StyleDeclaration::StyleDeclaration(const string& _name, const sp<Style>& _defaultStyle)
		:name(_name){
		 defaultStyle = _defaultStyle;
	}
	
	sp<Style>	StyleDeclaration::createStyle(){
		return defaultStyle->clone();
	}
}
