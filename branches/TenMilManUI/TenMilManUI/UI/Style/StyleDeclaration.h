#ifndef STYLEDECLARATION_H_
#define STYLEDECLARATION_H_

#include <tr1/memory>
#include <string>

#include "Styles/Style.h"

using std::string;
using std::tr1::shared_ptr;
using std::tr1::enable_shared_from_this;


namespace TenUI{
	
	class Style;
	
	class StyleDeclaration : public enable_shared_from_this<StyleDeclaration> {
	public:
		static shared_ptr<StyleDeclaration> create(const string& _name, const shared_ptr<Style>& _defaultStyle);
		
	public:
		virtual ~StyleDeclaration(){}
		
		const string& 		getName(){return name;}
		shared_ptr<Style>	createStyle();
		
	private:
		StyleDeclaration(const string& _name, const shared_ptr<Style>& _defaultStyle);
		
		string 				name;
		shared_ptr<Style> 	defaultStyle;
	};

}
#endif /*STYLEDECLARATION_H_*/
