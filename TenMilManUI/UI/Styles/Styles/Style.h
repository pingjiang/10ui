#ifndef STYLE_H_
#define STYLE_H_

#include "../StyleDeclaration.h"

#include <boost/any.hpp>
#include <string>
#include <tr1/memory>

using boost::any;
using boost::any_cast;
using std::string;
using std::tr1::shared_ptr;

class StyleDeclaration;

class Style {	
private:
	friend class StyleDeclaration;
	
public:	
	virtual ~Style(){}
	
	string getName();
	const shared_ptr<StyleDeclaration> getDeclaration();
	
	virtual any getValue() = 0;	
	virtual void setValue(const any& newValue) = 0;
	
	virtual shared_ptr<Style> clone() = 0;
	
protected:
	shared_ptr<StyleDeclaration> declaration;
};

#endif /*STYLE_H_*/
