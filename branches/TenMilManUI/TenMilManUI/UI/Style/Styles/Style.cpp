#include "Style.h"


namespace TenUI{
	string Style::getName(){
		return declaration->getName();
	}
	const sp<StyleDeclaration> Style::getDeclaration(){
		return declaration;
	}
}
