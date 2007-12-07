#include "StyleManager.h"

#include <iostream>
using std::cout;
using std::endl;

namespace TenUI{

	const string StyleManager::DefaultStyleSetName = "default";

	shared_ptr<StyleManager> StyleManager::inst = shared_ptr<StyleManager>(new StyleManager());
	shared_ptr<StyleManager> StyleManager::instance(){
		return StyleManager::inst;
	}
	
	StyleManager::StyleManager(){}
	
	StyleManager::~StyleManager(){}
	

	void StyleManager::registerUIComponent(shared_ptr<UIComponent> uiComps, const string& uiCompName, const string& parentUICompName){	
		cout << "registering: " << uiCompName << " parent: " << parentUICompName << endl;
		if(parentUICompName.size() > 0 ){
			UIComp_StateStyle_MapType::iterator parentSSDecl = compStyleMap.find(parentUICompName);
			if( parentSSDecl != compStyleMap.end() ){					
				shared_ptr<State_StyleDeclaration_MapType> newStateStyle(new State_StyleDeclaration_MapType());
				for(State_StyleDeclaration_MapType::iterator it=parentSSDecl->second->begin();
					it != parentSSDecl->second->end();
					++it){
					(*newStateStyle)[it->first] = it->second->clone();
				}
				compStyleMap[uiCompName] = newStateStyle;
			}
			
		}else{
			shared_ptr<State_StyleDeclaration_MapType> ssmap(new State_StyleDeclaration_MapType());
			(*ssmap)[DefaultStyleSetName] = shared_ptr<StyleSetDeclaration>(new StyleSetDeclaration("DefaultStyleSetName"));
			compStyleMap[ uiCompName ] = ssmap;			
		}
	}
	void StyleManager::addStyleDeclaration(const string& uiCompName, const shared_ptr<StyleDeclaration>& styleDecl){
		UIComp_StateStyle_MapType::iterator ssDecl = compStyleMap.find(uiCompName);
		if( ssDecl != compStyleMap.end() ){
			
			for(State_StyleDeclaration_MapType::iterator it=ssDecl->second->begin();
				it != ssDecl->second->end();
				++it){
				it->second->addStyleDeclaration(styleDecl);
			}
		}
	}
	
	shared_ptr< State_Style_MapType > StyleManager::getStateStyleSetMap(const string& uiCompName){
		UIComp_StateStyle_MapType::iterator ssDecl = compStyleMap.find(uiCompName);
		shared_ptr< State_Style_MapType > stateStyleMap(new State_Style_MapType());
		if( ssDecl != compStyleMap.end() ){
			for(State_StyleDeclaration_MapType::iterator it=ssDecl->second->begin();
				it != ssDecl->second->end();
				++it){
				cout << "State Name: " << it->first << endl;
				(*stateStyleMap)[it->first] = it->second->createStyleSet(); 
			}
			
			return stateStyleMap;
		}
		return shared_ptr<State_Style_MapType>(); 
	}
	
}
