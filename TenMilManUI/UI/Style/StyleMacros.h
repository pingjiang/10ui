#ifndef STYLEMACROS_H_
#define STYLEMACROS_H_

#include "Styles/Style.h"

/** CODE GENERATION BITCHES! **/


#define BEGIN_DECLARE_STYLES(theClass) 															\
	private:																					\
		static bool _styleInitializer(); 														\
		static const bool _styleInitializer_helper;												\
	private:																					\
		static vector<string> StyleNameVector;													\
		static vector< sp<Style> > DefaultStyleVector;											\
		static string		  _styleVector_helper(const string& temp, const sp<Style>& defaultStyle);
	
#define DECLARE_STYLE(stylename)																\
		static const string stylename##_style;
		
#define END_DECLARE_STYLES() 																	\
	
		
#define BEGIN_IMPL_STYLES(theClass) 															\
	vector<string> theClass::StyleNameVector;													\
	vector< sp<Style> > theClass::DefaultStyleVector;											\
	string theClass::_styleVector_helper(const string& temp, const sp<Style>& defaultStyle){	\
		theClass::StyleNameVector.push_back(temp);												\
		theClass::DefaultStyleVector.push_back(defaultStyle);									\
		return temp;																			\
	}
	

#define IMPL_STYLE(theClass, stylename, defaultStyle) 											\
	const string theClass::stylename##_style = theClass::_styleVector_helper(string(#stylename), sp<Style>(new defaultStyle));
		
#define END_IMPL_STYLES(theClass) 														\
	bool theClass::_styleInitializer(){													\
		for(unsigned int i=0; i<StyleNameVector.size(); ++i){							\
			StyleManager::instance()->addStyleDeclaration(								\
					theClass::getUICompName(),											\
					StyleDeclaration::create(											\
							StyleNameVector.at(i),										\
							DefaultStyleVector.at(i)									\
					)																	\
			);																			\
		}																				\
		return false; 																	\
	} 																					\
	const bool theClass::_styleInitializer_helper = _styleInitializer();

#endif /*STYLEMACROS_H_*/
