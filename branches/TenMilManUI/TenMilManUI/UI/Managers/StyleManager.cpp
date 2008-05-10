#include "StyleManager.h"
#include "UIComponentManager.h"

#include <iostream>
using std::cout;
using std::endl;

namespace TenUI{

	sp<StyleManager> StyleManager::instance(){ 
		static sp<StyleManager> myinst2(new StyleManager());
		return myinst2;
	}
	
	StyleManager::StyleManager(){}	
	StyleManager::~StyleManager(){}
	
	bool StyleManager::hasRegistered(const string& uiCompName){
		return (compStyleMap.find(uiCompName) != compStyleMap.end());
	}

	void StyleManager::registerUIComponent(const string& uiCompName){

		cout << "StyleManager::registerUIComponent( " << uiCompName << " )" <<endl;
		
		// UIComponent hasn't registered already
		if( !hasRegistered(uiCompName) && UIComponentManager::instance()->hasRegistered(uiCompName) ){
			// Copy styling from Super UIComponent
			if( !UIComponentManager::instance()->isRootUIComponent(uiCompName) ){
				if( hasRegistered(UIComponentManager::instance()->getSuperUIComponent(uiCompName)) ){
					UIComp_StyleDeclaration_MapType::iterator parentSDecl = compStyleMap.find( UIComponentManager::instance()->getSuperUIComponent(uiCompName));
					if(parentSDecl != compStyleMap.end()){
						compStyleMap[uiCompName] = parentSDecl->second->clone();
					}else{
						cout << "StyleManager::registerUIComponent(): " << UIComponentManager::instance()->getSuperUIComponent(uiCompName) << " is not registered!" << endl;
					}
				}else{
					cout << "StyleManager::registerUIComponent(): " << uiCompName << "'s super not registered!" << endl;
				}
			}else{
				compStyleMap[uiCompName] = sp<StyleSetDeclaration>(new StyleSetDeclaration(UIComponent::getStartStateID())); 
				cout << "StyleManager::registerUIComponent(): " << uiCompName << " is root UIComponent." << endl;
			}
		}else{
			cout << "StyleManager::registerUIComponent(): " << uiCompName << " has registered or UIComponentManager hasn't registered." << endl;
		}
	}
	void StyleManager::addStyleDeclaration(const string& uiCompName, const sp<StyleDeclaration>& styleDecl){
		if(hasRegistered(uiCompName)){
			compStyleMap[uiCompName]->addStyleDeclaration(styleDecl);
		}
	}
	void StyleManager::setStyleDeclaration(const string& uiCompName, const sp<StyleDeclaration>& styleDecl){
		if(hasRegistered(uiCompName)){
			compStyleMap[uiCompName]->setStyleDeclaration(styleDecl);
		}
	}
	sp< StyleSet > StyleManager::getStyleSet(const string& uiCompName){
		if(hasRegistered(uiCompName)){
			return compStyleMap[uiCompName]->createStyleSet();
		}else{
			cout << "StyleManager::getStyleSet(): " << uiCompName << " not registered. " << endl;
		}
		return sp< StyleSet >();
	}
	
}
