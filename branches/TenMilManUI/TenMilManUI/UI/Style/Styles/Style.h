#ifndef STYLE_H_
#define STYLE_H_

#include <boost/any.hpp>
#include <string>

#include <TenMilManUI/Util/SmartPointer.h>

#include "../StyleDeclaration.h"

using boost::any;
using boost::any_cast;
using std::string;

namespace TenUI{

	class StyleDeclaration;
	
	class Style {	
	private:
		friend class StyleDeclaration;
		
	public:	
		virtual ~Style(){}
		
		string getName();
		const sp<StyleDeclaration> getDeclaration();
		
		virtual any getValue() = 0;	
		virtual void setValue(const any& newValue) = 0;
		
		virtual sp<Style> clone() = 0;
		
	protected:
		sp<StyleDeclaration> declaration;
	};
}

#endif /*STYLE_H_*/
