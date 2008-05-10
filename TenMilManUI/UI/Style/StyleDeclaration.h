#ifndef STYLEDECLARATION_H_
#define STYLEDECLARATION_H_

#include <string>

#include <TenMilManUI/Util/SmartPointer.h>

#include "Styles/Style.h"

using std::string;

namespace TenUI{
	
	class Style;
	
	class StyleDeclaration : public enable_shared_from_this<StyleDeclaration> {
	public:
		static sp<StyleDeclaration> create(const string& _name, const sp<Style>& _defaultStyle);
		
	public:
		virtual ~StyleDeclaration(){}
		
		const string& 		getName(){return name;}
		sp<Style>	createStyle();
		
	private:
		StyleDeclaration(const string& _name, const sp<Style>& _defaultStyle);
		
		string 				name;
		sp<Style> 	defaultStyle;
	};

}
#endif /*STYLEDECLARATION_H_*/
