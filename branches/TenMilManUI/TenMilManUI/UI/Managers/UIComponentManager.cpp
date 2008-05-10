#include "UIComponentManager.h"

namespace TenUI{

	sp<UIComponentManager> UIComponentManager::instance(){
		static sp<UIComponentManager> myinst3(new UIComponentManager());		
		return myinst3;
	}
	
	UIComponentManager::UIComponentManager(){}	
	UIComponentManager::~UIComponentManager(){}
	

	void UIComponentManager::registerUIComponent(const string& name, const string& superName, const CreateFunc_Type& createFunc){
		cout << "UIComponentManager::registerUIComponent(" << name << "," << superName << " )" <<endl;
		if( !hasRegistered(name) ){
			nameCreateFuncMap[name] = createFunc;
			superNameMap[name] = superName;
		}else{
			cout << name << " registered already!" << endl;
		}
	}
	
	bool UIComponentManager::hasRegistered(const string& name){ 
		return (nameCreateFuncMap.find(name) != nameCreateFuncMap.end());
	}
	
	bool UIComponentManager::isRootUIComponent(const string& name){
		if( hasRegistered(name) ){
			if( superNameMap[name] == "UIComponent" ){
				return true;
			}
		}
		return false;
	}
	
	string UIComponentManager::getSuperUIComponent(const string& name){
		SuperName_MapType::iterator it = superNameMap.find(name); 
		if( it != superNameMap.end() ){
			return superNameMap[name];
		}else{
			return string();
		}
	}
	
	sp<UIComponent> UIComponentManager::createUIComponent(const string& name){
		Name_CreateFunc_MapType::iterator it = nameCreateFuncMap.find(name); 
		if( it != nameCreateFuncMap.end() ){
			return it->second();
		}
		return sp<UIComponent>();
	}
}
