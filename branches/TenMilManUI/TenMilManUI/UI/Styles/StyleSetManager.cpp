#include "StyleSetManager.h"

namespace TenUI{
	
	/******************************/
	/*  Singleton Implementation  */
	/******************************/ 
	StyleSetManager* StyleSetManager::self = new StyleSetManager();
	StyleSetManager* StyleSetManager::instance(){
		return self;
	}
	
	/******************************/
	/*  		Constructor       */
	/******************************/ 
	StyleSetManager::StyleSetManager(){}
	StyleSetManager::~StyleSetManager(){
		unordered_map<string, unordered_map< string, StyleSet* >* >::iterator it = uiCompStyleSets.begin();
		while(it != uiCompStyleSets.end()){
			unordered_map< string, StyleSet* >::iterator it2 = (it->second)->begin();
			delete it2->second;
		}
	}
	
	// Registers StyleSets for UIComp
	void StyleSetManager::registerUIComp(const string& base_uiCompName, const string& uiCompName, string styleSets[]){
		unordered_map<string, unordered_map< string, StyleSet* >* >::iterator it = uiCompStyleSets.find(uiCompName);
		
		// no other uicomp has been registered under that name
		if(it == uiCompStyleSets.end()){
			
		}
	}
	
	// Set Style Declaration for a Style
	void StyleSetManager::setUIComp_StyleDeclaration(const string& uiCompName, Style*){
		
	}
	
	// Set Style Declaration for a Style of a particular StyleSet
	void StyleSetManager::setUICompStyleSet_StyleDeclaration(const string& uiCompName, const string& styleSetName, Style*){
		
	}
		
	/***********************
	 * SingleStyle methods *
	 ***********************/
	int   			getIntStyle(	const string& name){
		
	}
	float 			getFloatStyle(	const string& name){
		
	}
	const ColorHex& getColorStyle(	const string& name){
		
	}
	const string& 	getEnumStyle(	const string& name){
		
	}
	const string& 	getStringStyle(	const string& name){
		
	}
	
	void setIntStyle(const string& name, int newValue){
		
	}
	void setFloatStyle(const string& name, float newValue){
		
	}
	void setColorStyle(const string& name, const ColorHex& newValue){
		
	}
	void setEnumStyle(const string& name, const string& newValue){
		
	}
	void setStringStyle(const string& name, const string& newValue){
		
	}
			
	/**********************
	 * ArrayStyle methods *
	 **********************/ 
	int   			getArrayIntStyle(	const string& name, unsigned int i){
		
	}
	float			getArrayFloatStyle(	const string& name, unsigned int i){
		
	}
	const ColorHex& getArrayColorStyle(	const string& name, unsigned int i){
		
	}
	const string& 	getArrayEnumStyle(	const string& name, unsigned int i){
		
	}
	const string& 	getArrayStringStyle(const string& name, unsigned int i){
		
	}
	
	void setArrayIntStyle(	 const string& name, unsigned int i, int newValue){
		
	}
	void setArrayFloatStyle( const string& name, unsigned int i, float newValue){
		
	}
	void setArrayColorStyle( const string& name, unsigned int i, const ColorHex& newValue){
		
	}
	void setArrayEnumStyle(	 const string& name, unsigned int i, const string& newValue){
		
	}
	void setArrayStringStyle(const string& name, unsigned int i, const string& newValue){
		
	}
}
