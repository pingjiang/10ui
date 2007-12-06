#ifndef STYLESETMANAGER_H_
#define STYLESETMANAGER_H_

#include <string>
#include <tr1/unordered_map>

#include "Style.h"
#include "StyleSet.h"

using namespace std;
using namespace std::tr1;

namespace TenUI{
	class StyleSetManager {

	/******************************/
	/*  Singleton Implementation  */
	/******************************/ 
	private:
		static StyleSetManager* self;
	private:
		static StyleSetManager* instance();
		StyleSetManager();
		
	protected:
		// key -> value
		// UIComponentName -> Map of Style Sets (StyleSet Name -> StyleSet)
		unordered_map< string, 
					   unordered_map< string, StyleSet*, hash<string> >*, 
					   hash<string> > uiCompStyleSets;
			
	public:
		virtual ~StyleSetManager();
	
		// Registers StyleSets for UIComp
		void registerUIComp(const string& base_uiCompName, const string& uiCompName, string styleSets[]);
		
		// Set Style Declaration for a Style
		void setUIComp_StyleDeclaration(const string& uiCompName, Style*);
		
		// Set Style Declaration for a Style of a particular StyleSet
		void setUICompStyleSet_StyleDeclaration(const string& uiCompName, const string& styleSetName, Style*);
		
		/***********************
		 * SingleStyle methods *
		 ***********************/
		int   			getIntStyle(	const string& name);
		float 			getFloatStyle(	const string& name);
		const ColorHex& getColorStyle(	const string& name);
		const string& 	getEnumStyle(	const string& name);
		const string& 	getStringStyle(	const string& name);
	
		void setIntStyle(const string& name, int newValue);
		void setFloatStyle(const string& name, float newValue);
		void setColorStyle(const string& name, const ColorHex& newValue);
		void setEnumStyle(const string& name, const string& newValue);
		void setStringStyle(const string& name, const string& newValue);
				
		/**********************
		 * ArrayStyle methods *
		 **********************/ 
		int   			getArrayIntStyle(	const string& name, unsigned int i);
		float			getArrayFloatStyle(	const string& name, unsigned int i);
		const ColorHex& getArrayColorStyle(	const string& name, unsigned int i);
		const string& 	getArrayEnumStyle(	const string& name, unsigned int i);
		const string& 	getArrayStringStyle(const string& name, unsigned int i);
	
		void setArrayIntStyle(	 const string& name, unsigned int i, int newValue);
		void setArrayFloatStyle( const string& name, unsigned int i, float newValue);
		void setArrayColorStyle( const string& name, unsigned int i, const ColorHex& newValue);
		void setArrayEnumStyle(	 const string& name, unsigned int i, const string& newValue);
		void setArrayStringStyle(const string& name, unsigned int i, const string& newValue);
		
	};

}

#endif /*STYLESETMANAGER_H_*/
