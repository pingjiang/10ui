#include "Style.h"


	string Style::getName(){
		return declaration->getName();
	}
	const shared_ptr<StyleDeclaration> Style::getDeclaration(){
		return declaration;
	}
