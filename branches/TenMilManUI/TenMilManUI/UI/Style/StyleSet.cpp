#include "StyleSet.h"
namespace TenUI{
	string 	StyleSet::getName(){return declaration->getName();}

	sp<StyleSet> StyleSet::clone(){
		return declaration->createStyleSet();
	}
	
}
